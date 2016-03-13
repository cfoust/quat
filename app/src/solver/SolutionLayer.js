var quat = quat || {};
quat.solver = quat.solver || {};

/* This layer displays the current solution (that is not necessarily solved)
by maintaining a bunch of WordLayers that correspond to what the user has
entered.*/
quat.solver.SolutionLayer = cc.Layer.extend({

    applyTheme: function(theme) {
        var textColor = theme.colors.text;
        this.currentWord.setColor(textColor);
        this.goalWord.setColor(textColor);
        this.prevWord.setColor(textColor);
        this.stepsWord.setColor(textColor);
    },

    ctor: function(puzzleLayer, width, height, fontSize) {
        this._super();

        this.puzzleLayer = puzzleLayer;

        var size = {width: width, height: height},
            fourths = width / 4,
            gap = width * 0.16,
            panelHeight = fontSize + (width * .09); // The bounds of the window

        this.size = size;
        this.fontSize = fontSize;
        this.panelHeight = panelHeight;

        // Used to display the current word for the user
        var currentWord = new quat.solver.WordNode(fontSize, gap);
        currentWord.x = width / 2;
        currentWord.y = height * 0.60;
        currentWord.recalculateBounds();
        this.addChild(currentWord);
        this.currentWord = currentWord;

        // Used exclusively for animating swiping backwards
        var prevWord = new quat.solver.WordNode(fontSize, gap);
        prevWord.x = fourths / 2;
        prevWord.y = panelHeight + (fontSize / 2) + fontSize;
        prevWord.changeWord('TEST');
        prevWord.setOpacity(0);
        prevWord.setVisible(false);
        this.addChild(prevWord);
        this.prevWord = prevWord;

        // Create a word to display the goal word
        var goalWord = new quat.solver.WordNode(fontSize, gap);
        goalWord.x = width / 2;
        goalWord.y = currentWord.y + fontSize * 1.10;
        goalWord.zIndex = 1;
        this.addChild(goalWord);
        this.goalWord = goalWord;

        // Create a word to display the steps count
        var smallFontSize = fontSize * 0.4;
        var stepsWord = new cc.LabelTTF("", "Ubuntu", smallFontSize);
        stepsWord.x = width / 2;
        stepsWord.y = height * 0.1;
        stepsWord.zIndex = 1;
        stepsWord.string = "STEPS: 0 PAR: 0";
        this.addChild(stepsWord);
        this.stepsWord = stepsWord;

        return true;
    },
    
    setCurrentWordOpacity: function(opacity) {
        this.currentWord.setOpacity(opacity);
    },

    setOpacity: function(opacity) {
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
        return this.currentWord.pointInWord(cc.p(x,y));
    },

    /**
     * Returns whether or not a given point is in one of the current word's
     * columns. If not, returns false, otherwise returns the letter's index.
     * @param  {number} x x coordinate in this object's space
     * @param  {number} y y coordinate in this object's space
     * @return {number or boolean} 
     */
    pointInColumn: function(x,y) {
        var bounds = this.currentWord.bounds;
        for (var i = 0; i < bounds.length; i++) {
            var bound = bounds[i];
            if ((x >= bound.x) && (x <= (bound.x + bound.width))) {
                return i;
            }
        }

        return false;
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

        if (!puzzle.timeStarted()) {
            puzzle.startTime();
        }

        this.currentWord.changeWord(puzzle.getCurrentWord());
        this.goalWord.changeWord(puzzle.getGoal());

        if (!puzzle.isSpecial()) {
            var steps = (puzzle.getSteps().length - 1),
                par = puzzle.getPar() - 1;

            this.stepsWord.string = "STEPS: " + steps.toString() + " PAR: " + par.toString();
        }
        
        this.stepsWord.setVisible(!puzzle.isSpecial());
    }
});