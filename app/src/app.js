var ChooseLetterLayer = cc.Layer.extend({
    setCurrent: function(word) {
        this.word = word.split("");
        this.mainWord = [];
    },
    ctor:function (font_size, font_gap) {
        //////////////////////////////
        // 1. super init first
        this._super();

        var size = cc.winSize,
            // A fourth of the width for regions
            fourths = size.width / 4;

        var font_total = (font_size + font_gap * 2);

        // We calculate how many letters can fit on the screen with our params
        var letterPoolCount = Math.ceil(size.height / font_total) + 1;

        // Total height of all the letters in the alphabet
        var totalHeight = 26 * font_total;

        // Create a pool because we only need so many
        var letterPool = [];
        for (var i = 0; i < letterPoolCount; i++) {
            // Initialize the label
            var letterLabel = new cc.LabelTTF("A", "Arial", font_size);
            letterLabel.x = -100;
            letterLabel.y = -100;
            this.addChild(letterLabel);
            letterPool.push(letterLabel);
        }
        

        var uppercase = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
        var offsetMajor = 0;
        var pos = 0;
        // Scrolls the letters to a certain offset
        var tletter = 0;
        var setScroll = function(offset) {
            /* If this isn't in here, things get messy.
               Yeah, we could fix this in the future to work like it should,
               but that's an S.E.P. if I've ever seen one.*/
            if ((offset % 100) == 0) {
                offset += .001;
            }

            /* Modulus has odd behavior in JS, have to use other logic*/
            if (offset < 0) {
                offset += totalHeight;
            } else {
                offset = offset % totalHeight;
            }

            // We have to inverse the offset because A-Z goes from top to bottom
            var relativeDiff = totalHeight - offset;
            // Get the index of the LAST letter displayed on the screen 
            var letter = (relativeDiff - (relativeDiff % font_total)) / font_total;
            // Get its location on the screen
            var location = -1*(offset % font_total) + (font_total / 2);

            // Iterate through all our letter objects
            for (var i = 0; i < letterPool.length; i++) {
                var letterObj = letterPool[i];
                letterObj.y = location + (i * font_total);

                var letterIndex = (letter - i + 1) % 26;
                
                if (letterIndex < 0) {
                    letterIndex += 26;
                }

                letterObj.string = uppercase[letterIndex % 26];
            }
        }

        var shown = false;
        var hideScroll = function() {
            shown = false;
            for (var i = 0; i < letterPool.length; i++) {
                letterPool[i].setOpacity(0);
            }
        }
        var showScroll = function(region) {
            shown = true;
            for (var i = 0; i < letterPool.length; i++) {
                var letterObj = letterPool[i];
                letterObj.x = (region * fourths) + (fourths / 2);
                letterObj.setOpacity(255);
            }
        }

        
        cc.eventManager.addListener({
            event: cc.EventListener.MOUSE,
            onMouseMove: function(event){
                if (!shown) {
                    return;
                }

                var delta = pos - event.getLocationY();
                // delta *= -1;
                setScroll(offsetMajor + delta);
            },
            onMouseUp: function(event){
                hideScroll();
            },
            onMouseDown: function(event){
                var x = event.getLocationX();

                // Records the original click position
                pos = event.getLocationY();

                // Gets the region the click was in (there are four, 0-3)
                var loc = (x - (x % fourths)) / fourths;
                
                // The letter (of LAKE) that we get the index of
                var letter = word[loc].charCodeAt(0) - 65;

                var offset = (totalHeight - (letter * font_total));
                

                offset = offset - (size.height / 2) + font_total / 2;

                // Remember the original offset we were at
                offsetMajor = offset;

                // Set the scroll position (should keep letter in middle)
                setScroll(offset);

                showScroll(loc);
            },
            onMouseScroll: function(event){
            }
        },colorBackground);

        return true;
    }
});

var WordNode = cc.Node.extend({
    /**
     * Creates a WordNode with the given font size.
     * @param  {number} fontSize The size of the font to be initialized.
     * @param  {number} fontGap The distance between each letter.
     */
    ctor: function (fontSize, fontGap) {
        this._super();

        // Store these for later
        this.fontSize = fontSize;
        this.fontGap = fontGap;

        // Create a pool of labels we can use to draw this word
        var rowPool = []
        for (var j = 0; j < 4; j++) {
            var letterLabel = new cc.LabelTTF("A", "Arial", fontSize);

            // Set them to be hidden
            letterLabel.x = (j * this.fontGap);
            letterLabel.y = 0;

            // Add it as a child to this layer
            this.addChild(letterLabel);

            rowPool.push(letterLabel);
        }
        this.rowPool = rowPool;

        return true;
    },

    /**
     * Replaces the text of this word with a given word.
     * @param  {[type]} word [description]
     */
    changeWord: function(word) {
        for (var j = 0; j < 4; j++) {
            var letterLabel = this.rowPool[j];
            letterLabel.string = word[j].toUpperCase();
        }
    },

    setColor: function(color) {
        for (var j = 0; j < 4; j++) {
            var letterLabel = this.rowPool[j];
            letterLabel.setFontFillColor(color);
        }
    }
});

/* This layer displays the current solution (that is not necessarily solved)
by maintaining a bunch of WordLayers that correspond to what the user has
entered.*/
var SolutionLayer = cc.Layer.extend({
    ctor: function(width, height) {
        this._super();

        var size = {width: width, height: height}, // The bounds of the window
            fourths = size.width / 4; // A fourth of the width for regions

        this.size = size;

        // Size of the font for every letter
        var font_size = size.width * 0.18;

        // Space on top and bottom of each letter (vertical)
        var font_gap = 10;

        var font_total = (font_size + font_gap * 2);

        // We calculate how many letters can fit on the screen with our params
        var letterPoolCount = Math.ceil(size.height / font_total) + 1;

        // Create a pool because we only need so many (enough to fill the screen)
        var letterPool = [];
        for (var i = 0; i < letterPoolCount; i++) {
            // There are four in each row
            var word = new WordNode(font_size, fourths);

            word.setVisible(false);
            word.x = fourths / 2;

            this.addChild(word);
            letterPool.push(word);
        }

        // Allow us to access it from other functions
        this.letterPool = letterPool;

        // Create a word to display the goal word
        var goalWord = new WordNode(font_size, fourths);
        goalWord.x = fourths / 2;
        goalWord.y = font_size / 2;
        goalWord.setColor(cc.color(0,255,0,255));
        this.addChild(goalWord);
        this.goalWord = goalWord;

        return true;
    },
    /**
     * Updates the view with a given solution.
     * @param  {Array} solution Array of four-letter words (strings).
     */
    updateSolution: function(solution) {
        // To filter out bad solutions
        if (solution.length < 1) {
            return;
        }

        // Have to do this so we don't mess up the original array
        var reversed = solution.slice().reverse();

        // Hide all of the words
        for (var i = 0; i < this.letterPool.length; i++) {
            var word = this.letterPool[i];
            word.setVisible(false);
        }

        for (var i = 0; i < reversed.length; i++) {
            var word = this.letterPool[i];
            word.y = (this.size.height / 2) + (i * 100);
            word.changeWord(reversed[i]);
            word.setVisible(true);
        }

    },

    updateGoal: function(goal) {
        var word = this.goalWord;
        word.changeWord(goal);
    }
});

var BackgroundLayer = cc.Layer.extend({
    ctor:function () {
        this._super();

        var colorBackground = new cc.LayerColor(cc.color(92,94,90,255));

        this.colorBackground = colorBackground;
        this.addChild(colorBackground);

        return true;
    }
});

var PuzzleScene = cc.Scene.extend({
    ctor: function(windowWidth, windowHeight) {
        this._super();

        this.windowWidth = windowWidth;
        this.windowHeight = windowHeight;

        return true;
    },

    /**
     * Calculates the size of the playing area based on the real resolution.
     *
     * Essentially, we can just fill the rest of the canvas up with the
     * background.
     * 
     * @return {Object} Object with 'width', 'height', 'x', and 'y'.
     */
    calculateSize: function() {
        var w = this.windowWidth,
            h = this.windowHeight,
            cWidth = 0, // The calculated width
            cHeight = h, // The calculated height (alwa)ys h)
            cX = 0, // The calculated X
            cY = 0; // The calculated Y (always 0)

        var NICE_WIDTH = 300;

        // Case 1: Landscape (and square) orientation
        if ((w >= h) || ((w < h) && (w > NICE_WIDTH))) {
            cWidth = Math.min(w, NICE_WIDTH);
            cX = (w / 2) - (cWidth / 2);
        // Case 2: Portrait orientation
        } else {
            cWidth = w;
            cX = 0;
        }

        return {
            width: cWidth,
            height: cHeight,
            x: cX,
            y: cY
        };
    },

    onEnter: function() {
        this._super();

        // Initialize the model and get a new puzzle
        var quatGame = new QuatModel();
        quatGame.newPuzzle();

        // Initialize our layers
        var backgroundLayer = new BackgroundLayer(),
            solutionSize = this.calculateSize(),
            solutionLayer = new SolutionLayer(solutionSize.width, 
                                              solutionSize.height);

        solutionLayer.x = solutionSize.x;
        solutionLayer.y = solutionSize.y;

        // Add each layer to this rendering target
        this.addChild(backgroundLayer);
        this.addChild(solutionLayer);

        // Have them be accessible from other methods (propogate)
        this.backgroundLayer = backgroundLayer;
        this.solutionLayer = solutionLayer;

        // Update the solution layer's current status and goal
        solutionLayer.updateSolution(quatGame.getCurrentSteps());
        solutionLayer.updateGoal(quatGame.getGoal());
    }
});

