var quat = quat || {};
quat.solver = quat.solver || {};

/* This layer displays the current solution (that is not necessarily solved)
by maintaining a bunch of WordLayers that correspond to what the user has
entered.*/
quat.solver.SolutionLayer = cc.Layer.extend({

    applyTheme: function(theme) {
        var textColor = theme.colors.text;
        this.currentWord.applyTheme(theme);
        this.goalWord.applyTheme(theme);
        this.stepsWord.setColor(textColor);
        this.score.setColor(textColor);
        this.undoIcon.applyTheme(theme);
    },

    ctor: function(puzzleLayer, gameBounds, fontSize) {
        this._super();

        this.puzzleLayer = puzzleLayer;

        var width = gameBounds.width,
            height = gameBounds.height;
            size = {width: width, height: height},
            fourths = width / 4,
            gap = width * 0.16,
            panelHeight = fontSize + (width * .09); // The bounds of the window

        this.size = size;
        this.fontSize = fontSize;
        this.panelHeight = panelHeight;

        // Used to display the current word for the user
        var currentWord = new quat.solver.BorderedWordNode(fontSize, gap);
        currentWord.x = gameBounds.x + (width / 2);
        currentWord.y = height * 0.6;
        currentWord.recalculateBounds();
        this.addChild(currentWord);
        this.currentWord = currentWord;

        // Create a word to display the goal word
        var goalWord = new quat.solver.WordNode(fontSize, gap);
        goalWord.x = gameBounds.x + (width / 2);
        goalWord.y = currentWord.y + fontSize * 1.10;
        goalWord.zIndex = 1;
        this.addChild(goalWord);
        this.goalWord = goalWord;


        var undoCallback = function(self) {
            return function() {
                var puzzleLayer = self.puzzleLayer,
                    game = puzzleLayer.quatGame;

                game.getPuzzle().goBack();
                self.updateFromModel(game);
            }
        }(this);
        var undoIcon = new quat.IconButton(fontSize * 0.8, "\uf0e2", undoCallback),
            firstBounds = currentWord.bounds[0];
        undoIcon.x = firstBounds.x - (fontSize * 1.1);
        undoIcon.y = currentWord.y - (fontSize * 0.50);
        undoIcon.enabled(true);
        this.undoIcon = undoIcon;
        this.addChild(undoIcon);

        // Create a word to display the steps count
        var smallFontSize = fontSize * 0.4;
        var stepsWord = new cc.LabelTTF("", "Ubuntu", smallFontSize);
        stepsWord.x = gameBounds.x + (width / 2);
        stepsWord.y = height * 0.1;
        stepsWord.zIndex = 1;
        stepsWord.string = "STEPS: 0 PAR: 0";
        this.addChild(stepsWord);
        this.stepsWord = stepsWord;


        var score = new cc.LabelTTF("", "Ubuntu", fontSize * 0.8);
        score.x = stepsWord.x;
        score.y = stepsWord.y + smallFontSize * 1.7;
        score.zIndex = 1;
        score.string = "";
        this.addChild(score);
        this.score = score;

        return true;
    },
    
    setCurrentWordOpacity: function(opacity) {
        this.currentWord.setOpacity(opacity);
    },

    setOpacity: function(opacity) {
        this.goalWord.setOpacity(opacity);
        this.currentWord.setOpacity(opacity);
        this.stepsWord.setOpacity(opacity);
        this.score.setOpacity(opacity);
        this.undoIcon.setOpacity(opacity);
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

        var steps = (puzzle.getSteps().length - 1),
            par = puzzle.getPar() - 1;
        this.stepsWord.string = "STEPS: " + steps.toString() + " PAR: " + par.toString();

        this.undoIcon.setVisible(puzzle.getSteps().length > 1);

        this.score.string = model.getUser().getPoints();
        
        // this.stepsWord.setVisible(!puzzle.isSpecial());
    }
});