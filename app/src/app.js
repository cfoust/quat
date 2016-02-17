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
    ctor:function () {
        this._super();

        var size = cc.winSize, // The bounds of the window
            fourths = size.width / 4; // A fourth of the width for regions

        this.size = size;

        // Size of the font for every letter
        var font_size = 80;

        // Space on top and bottom of each letter (vertical)
        var font_gap = 10;

        var font_total = (font_size + font_gap * 2);

        // We calculate how many letters can fit on the screen with our params
        var letterPoolCount = Math.ceil(size.height / font_total) + 1;

        // Total height of all the letters in the alphabet
        var totalHeight = 26 * font_total;

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
        goalWord.y = 50;
        goalWord.setColor(cc.color(0,255,0,255));
        this.addChild(goalWord);
        this.goalWord = goalWord;


        // var word = letterPool[0];
        // word.x = fourths / 2;
        // word.y = size.height / 2;
        // word.setVisible(true);
        // word.changeWord("FART");
        // var word = QUAT_PROBLEMS[0][0].split("");
        // var mainWord = [];
        // for (var j = 0; j < 4; j++) {
        //     var letterLabel = new cc.LabelTTF(word[j], "Arial", font_size);
        //     // position the label on the center of the screen
        //     letterLabel.x = (j * fourths) + (fourths / 2);
        //     letterLabel.y = size.height / 2;
        //     // add the label as a child to this layer
        //     this.addChild(letterLabel, 5);
        //     mainWord.push(letterLabel);
        // }

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

        this.addChild(colorBackground);

        return true;
    }
});

var PuzzleScene = cc.Scene.extend({
    onEnter:function () {
        this._super();

        var quatGame = new QuatModel();
        quatGame.newPuzzle();

        var backgroundLayer = new BackgroundLayer(),
            solutionLayer = new SolutionLayer();

        this.addChild(backgroundLayer);
        this.addChild(solutionLayer);

        solutionLayer.updateSolution(quatGame.getCurrentSteps());
        solutionLayer.updateGoal(quatGame.getGoal());
    }
});

