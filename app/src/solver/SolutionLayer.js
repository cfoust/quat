var quat = quat || {};
quat.solver = quat.solver || {};

/* This layer displays the current solution (that is not necessarily solved)
by maintaining a bunch of WordLayers that correspond to what the user has
entered.*/
quat.solver.SolutionLayer = cc.Layer.extend({

    applyTheme: function(theme) {
        var textColor = theme.colors.text;
        this.currentWord.setColor(textColor);
        this.prevWord.setColor(textColor);
        this.goalWord.setColor(theme.colors.darkForeground);
        this.stepsWord.setColor(theme.colors.darkForeground);
        this.goalBackground.setColor(theme.colors.lightForeground);
    },

    ctor: function(puzzleLayer, width, height, fontSize) {
        this._super();

        this.puzzleLayer = puzzleLayer;

        var size = {width: width, height: height},
            fourths = width / 4,
            panelHeight = fontSize + (width * .09); // The bounds of the window

        this.size = size;
        this.fontSize = fontSize;
        this.panelHeight = panelHeight;

        // Used to display the current word for the user
        var currentWord = new quat.solver.WordNode(fontSize, fourths);
        currentWord.x = fourths / 2;
        currentWord.y = panelHeight + (fontSize / 2);
        this.addChild(currentWord);
        this.currentWord = currentWord;

        // Used exclusively for animating swiping backwards
        var prevWord = new quat.solver.WordNode(fontSize, fourths);
        prevWord.x = fourths / 2;
        prevWord.y = panelHeight + (fontSize / 2) + fontSize;
        prevWord.changeWord('TEST');
        prevWord.setOpacity(0);
        this.addChild(prevWord);
        this.prevWord = prevWord;

        // Create a word to display the goal word
        var goalWord = new quat.solver.WordNode(fontSize, fourths);
        goalWord.x = fourths / 2;
        goalWord.y = panelHeight * 0.6;
        goalWord.zIndex = 1;
        this.addChild(goalWord);
        this.goalWord = goalWord;

        // Create a word to display the steps count
        var smallFontSize = panelHeight * 0.20,
            smallFontY = panelHeight * 0.17;
        var stepsWord = new cc.LabelTTF("", "Ubuntu", smallFontSize);
        // stepsWord.setAnchorPoint(new cc.Point(0,0.5));
        // stepsWord.x = (fourths * .23);
        stepsWord.x = width / 2;
        stepsWord.y = smallFontY;
        stepsWord.zIndex = 1;
        stepsWord.string = "STEPS: 0 PAR: 0";
        this.addChild(stepsWord);
        this.stepsWord = stepsWord;

        // Set up a background for the goal word
        var goalBackground = new cc.LayerColor(cc.color(0,191,255,255));
        goalBackground.height = panelHeight;
        goalBackground.width = size.width;
        goalBackground.zIndex = 0;
        this.goalBackground = goalBackground;
        this.addChild(goalBackground);

        return true;
    },



    
    setCurrentWordOpacity: function(opacity) {
        this.currentWord.setOpacity(opacity);
    },

    setOpacity: function(opacity) {
        this.goalBackground.setOpacity(opacity);
        this.goalWord.setOpacity(opacity);
        this.currentWord.setOpacity(opacity);
        this.stepsWord.setOpacity(opacity);
    },

    /**
     * Returns whether or not a given point is in one of the current word's
     * letters. If not, returns false, otherwise returns the letter's index.
     * @param  {number} x x coordinate in this object's space
     * @param  {number} y y coordinate in this object's space
     * @return {number or boolean} 
     */
    pointInCurrentWord: function(x,y) {
        var wordY1 = this.panelHeight,
            wordY2 = wordY1 + (this.fontSize);

        // Ensure the point is in the current word
        if ((x > this.size.width) ||
            (y > wordY2) ||
            (x < 0) ||
            (y < wordY1)) {
            return false;
        }

        var fourths = this.size.width / 4,
            loc = (x - (x % fourths)) / fourths;

        // Handles edge case where loc can be 4 if the border falls on a pixel
        if (loc >= 4) {
            return false;
        }

        return loc;
    },

    /**
     * Returns whether or not a given point is in one of the current word's
     * columns. If not, returns false, otherwise returns the letter's index.
     * @param  {number} x x coordinate in this object's space
     * @param  {number} y y coordinate in this object's space
     * @return {number or boolean} 
     */
    pointInColumn: function(x,y) {
        var wordY1 = this.panelHeight;
        if ((x < 0) || (x > this.size.width) || (y < wordY1)) {
            return false;
        }

        var fourths = this.size.width / 4,
            loc = (x - (x % fourths)) / fourths;

        return loc;
    },

    /**
     * Returns the y position of the bottom of the current word.
     * @return {number} The y position of the bottom of the current word.
     */
    bottomOfCurrentWord: function() {
        return this.panelHeight;
    },

    /**
     * Returns the y position of the top of the current word.
     * @return {number} The y position of the top of the current word.
     */
    topOfCurrentWord: function() {
        return this.bottomOfCurrentWord() + this.fontSize;
    },

    updateFromModel: function(model) {
        var puzzle = model.getPuzzle();

        if (puzzle.inProgress()) {
            puzzle.startTime();
        }

        this.currentWord.changeWord(puzzle.getCurrentWord());
        this.goalWord.changeWord(puzzle.getGoal());

        if (!puzzle.isSpecial()) {
            var steps = (puzzle.getSteps().length - 1),
                par = puzzle.getPar();

            this.stepsWord.string = "STEPS: " + steps.toString() + " PAR: " + par.toString();
        }
        
        this.stepsWord.setVisible(!puzzle.isSpecial());
    }
});