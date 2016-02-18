
/* A conglomeration of four labels we use to display a word. */
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

/* Layer for letting the user choose a new letter for a given one in
   the current word. */
var ChooseLetterLayer = cc.Layer.extend({
    ctor:function (width, height, fontSize) {
        this._super();
        var fontGap = 10;
        var fontTotal = (fontSize + fontGap * 2);

        // We calculate how many letters can fit on the screen with our params
        var letterPoolCount = Math.ceil(height / fontSize) + 1;
        console.log(letterPoolCount);

        // Total height of all the letters in the alphabet
        var totalHeight = 26 * fontTotal;

        // Create a pool because we only need so many
        var letterPool = [];
        for (var i = 0; i < letterPoolCount; i++) {
            // Initialize the label
            var letterLabel = new cc.LabelTTF("A", "Arial", fontSize);
            letterLabel.x = (width / 2);
            letterLabel.y = (fontTotal / 2) + fontSize + (i * fontSize);
            // letterLabel.y = (fontTotal / 2) + (i * fontSize);
            letterLabel.zIndex = 1;
            this.addChild(letterLabel);
            letterPool.push(letterLabel);
        }
        this.letterPool = letterPool;

        // Add a background behind the letter selector
        var colorBackground = new cc.LayerColor(cc.color(133,150,83,255));

        // Make it the same dimensions as the selector
        colorBackground.width = width;
        colorBackground.height = height;

        // Place it above the goal word
        colorBackground.y = (fontTotal / 2) + fontSize / 2;

        // Make it so the letters sit above it
        colorBackground.zIndex = 0;


        this.colorBackground = colorBackground;
        this.addChild(colorBackground);


        return true;
        

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
    },

    setBaseLetter: function(letter) {
        letter = letter.toUpperCase();
        var uppercase = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
        var index = letter.charCodeAt(0) - 65;

        for (var i = 0; i < this.letterPool.length; i++) {
            var letterLabel = this.letterPool[i];
            var newIndex = (index - i) % uppercase.length;
            if (newIndex < 0) {
                newIndex += uppercase.length;
            }
            letterLabel.string = uppercase[newIndex];
        }
    }
});


/* This layer displays the current solution (that is not necessarily solved)
by maintaining a bunch of WordLayers that correspond to what the user has
entered.*/
var SolutionLayer = cc.Layer.extend({
    ctor: function(width, height, fontSize) {
        this._super();

        var size = {width: width, height: height}, // The bounds of the window
            fourths = size.width / 4; // A fourth of the width for regions

        this.size = size;

        // Size of the font for every letter
        var fontSize = size.width * 0.18;
        this.fontSize = fontSize;

        // Space on top and bottom of each letter (vertical)
        var fontGap = 10;

        // The total size of every word/label
        var fontTotal = (fontSize + fontGap * 2);
        this.fontTotal = fontTotal;

        // We calculate how many words can fit on the screen
        var wordPoolCount = Math.ceil(size.height / fontTotal) + 1;

        // Create a pool because we only need so many
        var wordPool = [];
        for (var i = 0; i < wordPoolCount; i++) {
            // There are four in each row
            var word = new WordNode(fontSize, fourths);

            word.setVisible(false);
            word.x = fourths / 2;

            this.addChild(word);
            wordPool.push(word);
        }

        // Allow us to access it from other functions
        this.wordPool = wordPool;

        // Create a word to display the goal word
        var goalWord = new WordNode(fontSize, fourths);
        // Set it to be at the bottom of the screen
        goalWord.x = fourths / 2;
        goalWord.y = fontTotal / 2;
        goalWord.zIndex = 1;

        goalWord.setColor(cc.color(62,33,74,255));
        
        this.addChild(goalWord);
        this.goalWord = goalWord;

        // Set up a background for the goal word
        var goalBackground = new cc.LayerColor(cc.color(125,150,53,255));

        goalBackground.height = (fontTotal / 2) + (fontSize / 2);
        goalBackground.width = size.width;
        goalBackground.zIndex = 0;

        this.goalBackground = goalBackground;
        this.addChild(goalBackground);

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
        for (var i = 0; i < this.wordPool.length; i++) {
            var word = this.wordPool[i];
            word.setVisible(false);
        }

        // Set up a word for every word in the solution.
        for (var i = 0; i < reversed.length; i++) {
            var word = this.wordPool[i];
            word.y = (this.fontTotal / 2) + this.fontSize + (i * this.fontSize);
            word.changeWord(reversed[i]);
            word.setVisible(true);
        }

    },

    updateGoal: function(goal) {
        var word = this.goalWord;
        word.changeWord(goal);
    }
});

// Colored background layer
var BackgroundLayer = cc.Layer.extend({
    ctor:function () {
        this._super();

        var colorBackground = new cc.LayerColor(cc.color(63,74,33,255));

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
            fontSize = solutionSize.width * 0.18,
            solutionLayer = new SolutionLayer(solutionSize.width, 
                                              solutionSize.height,
                                              fontSize),
            chooseLetterLayer = new ChooseLetterLayer(
                                              solutionSize.width / 4,
                                              solutionSize.height,
                                              fontSize);

        chooseLetterLayer.setBaseLetter('D');
        chooseLetterLayer.setVisible(false);

        // Sets the solution layer to have its calculated bounds
        solutionLayer.x = solutionSize.x;
        solutionLayer.y = solutionSize.y;

        chooseLetterLayer.x = solutionSize.x;
        chooseLetterLayer.y = solutionSize.y;

        // Add each layer to this rendering target
        this.addChild(backgroundLayer);
        this.addChild(solutionLayer);
        this.addChild(chooseLetterLayer);

        // Have them be accessible from other methods
        this.backgroundLayer = backgroundLayer;
        this.solutionLayer = solutionLayer;
        this.chooseLetterLayer = chooseLetterLayer;

        // Update the solution layer's current status and goal
        solutionLayer.updateSolution(quatGame.getCurrentSteps());
        solutionLayer.updateGoal(quatGame.getGoal());

        cc.eventManager.addListener({
            event: cc.EventListener.MOUSE,
            onMouseMove: function(event){
                // console.log(event);
            },
            onMouseUp: function(event){
                chooseLetterLayer.setVisible(false);
            },
            onMouseDown: function(event){
                var x = event._x - solutionSize.x,
                    y = event._y - solutionSize.y,
                    fourths = solutionSize.width / 4,
                    loc = (x - (x % fourths)) / fourths,
                    newX = (loc * fourths) + solutionSize.x;

                chooseLetterLayer.x = newX;
                chooseLetterLayer.setBaseLetter(quatGame.getCurrentWord()[loc]);
                chooseLetterLayer.setVisible(true);
            },
            onMouseScroll: function(event){
            }
        },this);

        // Touch listener (kind of buggy, hard to test)
        // cc.eventManager.addListener({
        //     event: cc.EventListener.TOUCH_ONE_BY_ONE,
        //     swallowTouches: true,
        //     onTouchBegan: function(event){
        //         console.log(event);
        //     },
        //     onTouchMoved: function(event){
        //         console.log(event);
        //     },
        //     onTouchEnded: function(event){
        //         console.log(event);
        //     }
        // },this);
    }
});

