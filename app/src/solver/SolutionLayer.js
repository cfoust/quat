var quat = quat || {};
quat.solver = quat.solver || {};

/* This layer displays the current solution (that is not necessarily solved)
by maintaining a bunch of WordLayers that correspond to what the user has
entered.*/
quat.solver.SolutionLayer = cc.Layer.extend({
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
            var word = new quat.solver.WordNode(fontSize, fourths);

            word.setVisible(false);
            word.x = fourths / 2;

            this.addChild(word);
            wordPool.push(word);
        }

        // Allow us to access it from other functions
        this.wordPool = wordPool;

        // Create a word to display the goal word
        var goalWord = new quat.solver.WordNode(fontSize, fourths);
        var panelHeight = (fontTotal / 2) + (fontSize / 2);
        // Set it to be at the bottom of the screen
        goalWord.x = fourths / 2;
        goalWord.y = panelHeight / 2;
        goalWord.zIndex = 1;

        goalWord.setColor(cc.color(62,33,74,255));
        
        this.addChild(goalWord);
        this.goalWord = goalWord;

        // Set up a background for the goal word
        var goalBackground = new cc.LayerColor(cc.color(125,150,53,255));

        goalBackground.height = panelHeight;
        goalBackground.width = size.width;
        goalBackground.zIndex = 0;

        this.goalBackground = goalBackground;
        this.addChild(goalBackground);

        return true;
    },

    /**
     * Returns whether or not a given point is in one of the current word's
     * letters. If not, returns false, otherwise returns the letter's index.
     * @param  {number} x x coordinate in this object's space
     * @param  {number} y y coordinate in this object's space
     * @return {number or boolean} 
     */
    pointInCurrentWord: function(x,y) {
        var wordY1 = (this.fontTotal / 2) + (this.fontSize / 2),
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
        var wordY1 = (this.fontTotal / 2) + (this.fontSize / 2);
        if ((x < 0) || (x > this.size.width) || (y < wordY1)) {
            return false;
        }

        var fourths = this.size.width / 4,
            loc = (x - (x % fourths)) / fourths;

        return loc;
    },

    bottomOfCurrentWord: function() {
        return (this.fontTotal / 2) + (this.fontSize / 2);
    },

    topOfCurrentWord: function() {
        return this.bottomOfCurrentWord() + this.fontSize;
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
        for (var i = 0; i < Math.min(reversed.length, this.wordPool.length); i++) {
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