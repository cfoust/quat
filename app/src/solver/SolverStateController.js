var quat = quat || {};
quat.solver = quat.solver || {};

quat.solver.SolverStateController = quat.StateController.extend({
    states:  {
        /*
        When only the current solution progress is showing.
         */
        IDLE: function(self) {
            if ((self.state == self.states.CHANGING_LETTER_NODRAG) ||
                (self.state == self.states.CHOOSING_LETTER)) {
                self.sliderLayer.setVisible(false);
                self.keyboardLayer.setVisible(false);
            }

            if (!self.solutionLayer._slider) {
                self.solutionLayer.currentWord.unselect();
            }

            self.solutionLayer.stepsWord.setVisible(true);
            self.solutionLayer.score.setVisible(true);
            self.puzzleLayer.textIndicatorLayer.setVisible(true);

            self.solutionLayer.updateFromModel(self.quatGame);
        },
        /*
        When the user clicked on one of the letters in the current word,
        but has not dragged out of the current word yet.
         */
        CHOOSING_LETTER: function(self,args) {
            var column = args[0];

            var sliderEnabled = self.puzzleLayer._slider;

            self.sliderLayer.setVisible(sliderEnabled);
            self.solutionLayer.stepsWord.setVisible(sliderEnabled);
            self.solutionLayer.score.setVisible(sliderEnabled);
            self.puzzleLayer.textIndicatorLayer.setVisible(sliderEnabled);
            self.keyboardLayer.setVisible(!sliderEnabled);
            
            if (self.puzzleLayer._slider) {
                // Move the letter chooser to its proper location
                self.sliderLayer.setBaseLetter(self.quatGame.getPuzzle().getCurrentWord()[column]);
                self.sliderLayer.appear(column);
            } else {
                var currentWord = self.solutionLayer.currentWord;
                currentWord.unselect();
                currentWord.select(column);
            }

            self.setState(self.states.CHOOSING_LETTER);
        },
        /*
        The user has dragged out of the current word (selecting a new
        letter) and has stayed in a single column. The letter chooser is still
        tied to the mouse.
         */
        CHANGING_LETTER_DRAG: 2,
        /*
        The user has stopped dragging, but the letter chooser is still visible
        and is in the place they left it. They can either tap on the letter to
        enter it into the solution or drag again.
         */
        CHANGING_LETTER_NODRAG: 3,
        /*
        The user started dragging in the solution space outside of the current
        word.
         */
        GESTURING: 4,
        /*
        The user has started swiping to the left to erase a word.
         */
        ERASING_WORD: 5
    },

    init: function(puzzleScene) {
        this._super();

        // Grab all the references to things we need from puzzleScene
        this.quatGame = puzzleScene.quatGame;
        this.puzzleLayer = puzzleScene;
        this.backgroundLayer = puzzleScene.backgroundLayer;
        this.solutionLayer = puzzleScene.solutionLayer;
        this.sliderLayer = puzzleScene.sliderLayer;
        this.keyboardLayer = puzzleScene.keyboardLayer;
        this.gameBounds = puzzleScene.gameBounds;
    }
});