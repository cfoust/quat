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
            var currentLetter = this.solutionLayer.pointInCurrentWord(x,y);
            if (this.puzzleLayer._slider) {
                var currentColumn = this.solutionLayer.pointInColumn(x,y);

                /*
                If we have the letter chooser open and the user clicks on another 
                letter in the current word.
                 */
                if ((currentLetter !== false) && (currentColumn != this.lastColumn)) {
                    this.lastColumn = currentLetter;
                    this.sc.CHOOSING_LETTER(currentLetter);
                }
                else if (currentColumn == this.lastColumn) {
                    // Get the letter at this point on the letter chooser
                    this.lastColumn = currentColumn;
                    this.lastLetter = this.sliderLayer.letterAtY(y);
                    this.sc.CHANGING_LETTER_DRAG();
                }
                else {
                    this.sc.IDLE();
                }
            } else {
                var point = cc.p(x,y);
                var onBoard = this.keyboardLayer.pointInKeyboard(point),
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
        }
        else if (this.sc.state == this.sc.states.CHANGING_LETTER_NODRAG) {
            var currentLetter = this.solutionLayer.pointInCurrentWord(x,y),
                currentColumn = this.solutionLayer.pointInColumn(x,y);

            if ((currentColumn != this.lastColumn) && (currentLetter !== false)) {
                this.lastColumn = currentLetter;
                this.sc.CHOOSING_LETTER(currentLetter);
            }
            else if ((currentLetter === false) && (currentColumn != this.lastColumn)) {
                this.sc.IDLE();
            }
            else {
                // Get the letter at this point on the letter chooser
                this.lastLetter = this.sliderLayer.letterAtY(y);
                this.sc.CHANGING_LETTER_DRAG();
            }
        }
    },

    moved: function(x, y) {
        /*
        The user is choosing the letter they want to change.
         */
        if (this.sc.state == this.sc.states.CHOOSING_LETTER) {
            if (this.puzzleLayer._slider) {
                /*
                Gets the index of the letter the input is hovering over, or false if it
                is not over any letter.
                 */
                var currentLetter = this.solutionLayer.pointInCurrentWord(x,y);

                /*
                The input moved out of the letter it started dragging from, but not
                into another letter.
                 */
                if (currentLetter === false) {
                    var currentColumn = this.solutionLayer.pointInColumn(x,y);

                    // If the user stayed within the current column
                    if (currentColumn == this.lastColumn) {
                        this.sc.CHANGING_LETTER_DRAG();
                        var offset = y - this.lastDown.y;
                        this.sliderLayer.setOffset(offset);

                    // Otherwise close everything out
                    } else {
                        this.sc.IDLE();
                    }
                /*
                The input moved to another letter, so let's move the letter chooser to
                that letter.
                 */
                } else {
                    this.sc.CHOOSING_LETTER(currentLetter);
                    this.lastColumn = currentLetter;
                }
            } else {
                var point = cc.p(x,y),
                    onBoard = this.keyboardLayer.pointInKeyboard(point),
                    letter = this.keyboardLayer.pointInLetter(point);

                if (letter !== false) {
                    var currentWord = this.solutionLayer.currentWord,
                        column = this.lastColumn;
                    currentWord.changeLetter(column, letter);
                }
            }
            
        }
        /*
        The user is dragging the letter chooser.
         */
        else if (this.sc.state == this.sc.states.CHANGING_LETTER_DRAG) {
            // Change the letter chooser's offset to reflect the new input position.
            var offset = y - this.lastDown.y;
            this.sliderLayer.setOffset(offset);
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
        this.sliderLayer.setVisible(false);
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

        // Update the solution layer to match the new game state
        this.solutionLayer.updateFromModel(this.quatGame);
    },

    done: function(x, y) {
        /*
        The user slid along the current word to bring up the letter choosers, but
        never dragged upwards to start changing a letter. We just hide the chooser.
         */

        /*
        The user stopped dragging after starting to move the letter chooser.
         */
        if (this.sc.state == this.sc.states.CHANGING_LETTER_DRAG) {
            var currentLetter = this.solutionLayer.pointInCurrentWord(x,y),
                currentChooserLetter = this.sliderLayer.letterAtY(y),
                currentColumn = this.solutionLayer.pointInColumn(x,y);

            /*
            The user tapped on a letter in the letter chooser. Let's select that letter.
             */
            if ((currentLetter === false) && 
                     (currentColumn !== false) &&
                     (currentChooserLetter == this.lastLetter)) {
                this.sliderLayer.setBaseLetter(this.lastLetter);
                this.sc.CHANGING_LETTER_NODRAG();
            }
            /*
            The user stopped dragging outside of a letter, so we keep the letter
            chooser up and let them keep manipulating it.
             */
            else if ((currentLetter === false) && (currentColumn !== false)) {
                // Resets the base letter to the current letter. 
                // This looks nonsensical, but it's a problem of method naming more
                // than anything. The getBaseLetter() method returns the CURRENT
                // letter at the bottom instead of the REAL base letter before any
                // offset.
                this.sliderLayer.setBaseLetter(this.sliderLayer.getBaseLetter());
                this.sc.CHANGING_LETTER_NODRAG();
            }
            /*
            The user stopped dragging or touched inside a letter after selecting a 
            letter with the letter chooser, so we enter their choice.
             */
            else if ((currentLetter === this.lastColumn) && (currentColumn == this.lastColumn)) {
                this.finishWord();
            } else {
                this.sc.CHANGING_LETTER_NODRAG();
            }
        }
        else if ((this.sc.state == this.sc.states.CHOOSING_LETTER) && !this.puzzleLayer._slider) {
            var point = cc.p(x,y),
                onBoard = this.keyboardLayer.pointInKeyboard(point),
                letter = this.keyboardLayer.pointInLetter(point);

            if (letter !== false) {
                this.finishWord();
            }
        }
        /*
        The user tapped on a letter in the current word after choosing a letter.
         */
        else if (this.sc.state == this.sc.states.CHANGING_LETTER_NODRAG) {
            this.finishWord();   
        }
        else if (this.sc.state == this.sc.states.GESTURING) {
            this.sc.IDLE();
        }
    }
});