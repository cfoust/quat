var quat = quat || {};
quat.solver = quat.solver || {};

quat.solver.SolverStateController = quat.StateController.extend({
    states: {
        /*
        When only the current solution progress is showing.
         */
        IDLE: function(self) {
            if ((self.state == self.states.CHANGING_LETTER_NODRAG) ||
                (self.state == self.states.CHOOSING_LETTER)) {
                self.chooseLetterLayer.setVisible(false);
            }
            self.solutionLayer.updateSolution(self.quatGame.getCurrentSteps());
        },
        /*
        When the user clicked on one of the letters in the current word,
        but has not dragged out of the current word yet.
         */
        CHOOSING_LETTER: function(self, arguments) {
            var column = arguments[0];

            // Move the letter chooser to its proper location
            self.chooseLetterLayer.x = (column * (self.solutionSize.width / 4)) + self.solutionSize.x;
            self.chooseLetterLayer.setBaseLetter(self.quatGame.getCurrentWord()[column]);
            self.chooseLetterLayer.setVisible(true);
        },
        /*
        The user has dragged out of the current word (selecting a new
        letter) and has stayed in a single column. The letter chooser is still
        tied to the mouse.
         */
        CHANGING_LETTER_DRAG: null,
        /*
        The user has stopped dragging, but the letter chooser is still visible
        and is in the place they left it. They can either tap on the letter to
        enter it into the solution or drag again.
         */
        CHANGING_LETTER_NODRAG: null,
        /*
        The user started dragging in the solution space outside of the current
        word.
         */
        GESTURING: null,
        /*
        The user has started swiping to the left to erase a word.
         */
        ERASING_WORD: null,
        /*
        The user has started swiping to the right to get to the main menu.
         */
        SWIPING_TO_MENU: null
    },

    init: function(puzzleScene) {
        this._super();
        // Grab all the references to things we need from puzzleScene
        this.quatGame = puzzleScene.quatGame;
        this.backgroundLayer = puzzleScene.backgroundLayer;
        this.solutionLayer = puzzleScene.solutionLayer;
        this.chooseLetterLayer = puzzleScene.chooseLetterLayer;
        this.solutionSize = puzzleScene.solutionSize;


        // Sets the current state to IDLE
        this.state = this.states.IDLE;

        // Setting this to true prints every state change
        this.developer = false;

        var states = this.states;
        var stateToText = function(state) {
            var keys = Object.keys(states);
            return keys[state];
        }

        this.setState = function(state) {
            if (this.developer) {
                console.log(stateToText(this.state) + "->" + stateToText(state));
            }
            this.state = state;
        };

        // Records the previous y offset of the last drag action
        this.previousOffset = 0;
    }

});