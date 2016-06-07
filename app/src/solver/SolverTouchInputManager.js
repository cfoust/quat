var quat = quat || {};
quat.solver = quat.solver || {};

/**
 * Handles coordinate-based inputs for the puzzleLayer class. Transitions
 * from state to state and manipulates the game based on user input.
 */
quat.solver.SolverTouchInputManager = quat.TouchInputManager.extend({
    init: function(puzzleLayer) {
        this._super();

        // Grab all the references to things we need from puzzleLayer
        this.quatGame = puzzleLayer.quatGame;
        this.puzzleLayer = puzzleLayer; 
        this.solutionLayer = puzzleLayer.solutionLayer;
        this.gameBounds = puzzleLayer.gameBounds;
        this.sliderLayer = puzzleLayer.sliderLayer;
        this.keyboardLayer = puzzleLayer.keyboardLayer;
        this.textIndicatorLayer = puzzleLayer.textIndicatorLayer;
        this.sc = puzzleLayer.stateController;

        // Used to track the last column the user had clicked in
        this.lastColumn = -1;

        this.lastLetter = "";

        // Records the previous y offset of the last drag action
        this.previousOffset = 0;

        this.currentWordPos = this.solutionLayer.currentWord.y;
        this.currentWordPos = this.solutionLayer.currentWord.y;

        this.gestureThreshold = this.gameBounds.width * 0.03;
        this.distanceThreshold = this.gameBounds.width * 0.61;
    },

    began: function(x, y) {    
        if (this.sc.state == this.sc.states.IDLE) {
            // Check to see if this is a click in the current word
            var currentLetter = this.solutionLayer.pointInCurrentWord(x,y);

            if (currentLetter !== false) {
                this.lastColumn = currentLetter;
                this.sc.CHOOSING_LETTER(currentLetter);
            }
        }
        else if (this.sc.state == this.sc.states.CHOOSING_LETTER) {
            var currentLetter = this.solutionLayer.pointInCurrentWord(x,y),
                point = cc.p(x,y),
                onBoard = this.keyboardLayer.pointInKeyboard(point),
                boardLetter = this.keyboardLayer.pointInLetter(point);

            // User tapped on another letter
            if (currentLetter !== false) {
                this.sc.CHOOSING_LETTER(currentLetter);
                this.lastColumn = currentLetter;
            // User tapped somewhere not on the keyboard
            } else if (!onBoard) {
                this.sc.IDLE();
            // Only happens if they tapped on the keyboard in a letter
            } else if (boardLetter !== false) {
                var currentWord = this.solutionLayer.currentWord,
                    column = this.lastColumn;
                currentWord.changeLetter(column, boardLetter);
            }
        }
    },

    moved: function(x, y) {
        /*
        The user is choosing the letter they want to change.
         */
        if (this.sc.state == this.sc.states.CHOOSING_LETTER) {
            var point = cc.p(x,y),
                onBoard = this.keyboardLayer.pointInKeyboard(point),
                letter = this.keyboardLayer.pointInLetter(point),
                wordLetter = this.solutionLayer.pointInCurrentWord(x,y);

            // If they moved over a key on the keyboard
            if (letter !== false) {
                var currentWord = this.solutionLayer.currentWord,
                    column = this.lastColumn;
                currentWord.changeLetter(column, letter);

            // Lets you drag across the current word
            } else if ((wordLetter !== false) && (this.lastColumn != wordLetter)) {
                this.sc.CHOOSING_LETTER(wordLetter);
                this.lastColumn = wordLetter;
            }
            
        }
        else if (this.sc.state == this.sc.states.GESTURING) {
            var vector = this.calculateVector(x,y),
                angle = vector.angle,
                distance = vector.distance;
        }
    },

    finishWord: function() {
        

        // Calculate the new word
        var oldWord = this.quatGame.getPuzzle().getCurrentWord(), 
            newWord = null;
        if (this.puzzleLayer._slider) {
            newWord = oldWord.substr(0,this.lastColumn) + this.sliderLayer.getBaseLetter() + oldWord.substr(this.lastColumn + 1);
        } else {
            newWord = this.solutionLayer.currentWord.getWord();
        }

        // Set the state to be idle
        this.sc.IDLE();

        // Hide the letter choosers
        this.keyboardLayer.setVisible(false);

        newWord = newWord.toLowerCase();

        // Grab some references to the current game and puzzle
        var quatGame = this.quatGame,
            puzzle = quatGame.getPuzzle();

        // Attempt to add the word to the solution
        puzzle.addWord(newWord);

        // If the puzzle has a message it wants to be shown to the user
        if (puzzle.hasMessage()) {
            // Consume it and add it to the indicator
            var message = puzzle.consumeMessage();
            this.textIndicatorLayer.addMessage(message.text, message.special);
        }

        // Check if the puzzle is now done
        if (puzzle.isDone()) {
            // If so, take down all its stats
            this.quatGame.getUser().registerPuzzle(puzzle);

            this.puzzleLayer.textIndicatorLayer.clearMessages();

            if (puzzle.getSteps().length == puzzle.getPar()) {
                this.puzzleLayer.finishedLayer.par();
            } else {
                this.puzzleLayer.finishedLayer.done();
            }

            // Grab a new puzzle
            this.quatGame.newPuzzle();

            puzzle = quatGame.getPuzzle();

            // If the puzzle has a message it wants to be shown to the user
            if (puzzle.hasMessage() && puzzle.isSpecial()) {
                this.textIndicatorLayer.clearMessages();

                // Consume it and add it to the indicator
                var message = puzzle.consumeMessage();
                this.textIndicatorLayer.addMessage(message.text, message.special);
            }

            puzzle.startTime();

        }

        // Dump the current game state to localstorage
        quatGame.saveToLocal();
        quatGame.loadFromLocal();

        // Update the solution layer to match the new game state
        this.solutionLayer.updateFromModel(this.quatGame);
    },

    done: function(x, y) {
        if (this.sc.state == this.sc.states.CHOOSING_LETTER) {
            var point = cc.p(x,y),
                onBoard = this.keyboardLayer.pointInKeyboard(point),
                letter = this.keyboardLayer.pointInLetter(point);

            if (letter !== false) {
                this.finishWord();
            }
        }
        else if (this.sc.state == this.sc.states.GESTURING) {
            this.sc.IDLE();
        }
    }
});