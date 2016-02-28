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
        this.chooseLetterLayer = puzzleLayer.chooseLetterLayer;
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
            } else if (y > this.solutionLayer.topOfCurrentWord()) {
                this.sc.GESTURING();
            }
        }
        else if (this.sc.state == this.sc.states.CHOOSING_LETTER) {
            var currentLetter = this.solutionLayer.pointInCurrentWord(x,y),
                currentColumn = this.solutionLayer.pointInColumn(x,y);

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
                this.lastLetter = this.chooseLetterLayer.letterAtY(y - this.solutionLayer.bottomOfCurrentWord());
                this.sc.CHANGING_LETTER_DRAG();
            }
            else {
                this.sc.IDLE();
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
                this.lastLetter = this.chooseLetterLayer.letterAtY(y - this.solutionLayer.bottomOfCurrentWord());
                this.sc.CHANGING_LETTER_DRAG();
            }
        }
    },

    moved: function(x, y) {
        /*
        The user is choosing the letter they want to change.
         */
        if (this.sc.state == this.sc.states.CHOOSING_LETTER) {
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
                    this.chooseLetterLayer.setOffset(offset);

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
        }
        /*
        The user is dragging the letter chooser.
         */
        else if (this.sc.state == this.sc.states.CHANGING_LETTER_DRAG) {
            // Change the letter chooser's offset to reflect the new input position.
            var offset = y - this.lastDown.y;
            this.chooseLetterLayer.setOffset(offset);
        }
        else if (this.sc.state == this.sc.states.GESTURING) {
            var vector = this.calculateVector(x,y),
                angle = vector.angle,
                distance = vector.distance;
            
            // The user is dragging from right to left
            if (((Math.PI - Math.abs(angle)) <= 0.30) &&
                (distance > this.gestureThreshold) &&
                (this.quatGame.getPuzzle().getSteps().length > 1)) {
                this.solutionLayer.prevWord.changeWord(this.quatGame.getPuzzle().getPreviousWord());
                this.solutionLayer.prevWord.setOpacity(0);
                this.solutionLayer.currentWord.setOpacity(255);
                this.sc.ERASING_WORD();
            }
        }
        else if (this.sc.state == this.sc.states.ERASING_WORD) {
            var vector = this.calculateVector(x,y),
                angle = vector.angle,
                distance = vector.distance,
                solutionLayer = this.solutionLayer;

            // The user is dragging and has maintained the strict right-to-left
            // angle. They have to stay within 0.3 radians the whole time
            if ((Math.PI - Math.abs(angle)) <= 0.30) {
                var percent = (this.distanceThreshold - distance) / this.distanceThreshold,
                    fadeOutPercent = Math.min((percent * 255) + 30, 255),
                    fadeInPercent = Math.max(Math.min(255 - fadeOutPercent, 255), 0),
                    movePercent = Math.max(solutionLayer.fontSize * percent,0);

                // Fade in and out the current and previous words
                solutionLayer.currentWord.setOpacity(fadeOutPercent);
                solutionLayer.prevWord.setOpacity(fadeInPercent);

                // Make it look like the previous word is coming down onto the
                // current one to replace it
                solutionLayer.prevWord.y = solutionLayer.currentWord.y + movePercent;
            // Looks like they decided otherwise, stop tracking this touch
            } else {
                solutionLayer.currentWord.setOpacity(255);
                solutionLayer.prevWord.setOpacity(0);
                solutionLayer.prevWord.y = solutionLayer.currentWord.y + solutionLayer.fontSize;
                this.sc.GESTURING();
            }
        }
    },

    finishWord: function() {
        // Set the state to be idle
        this.sc.IDLE();

        // Hide the letter chooser
        this.chooseLetterLayer.setVisible(false);

        // Calculate the new word
        var oldWord = this.quatGame.getPuzzle().getCurrentWord(),
            newWord = oldWord.substr(0,this.lastColumn) + this.chooseLetterLayer.getBaseLetter() + oldWord.substr(this.lastColumn + 1);

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
                currentChooserLetter = this.chooseLetterLayer.letterAtY(y - this.solutionLayer.bottomOfCurrentWord()),
                currentColumn = this.solutionLayer.pointInColumn(x,y);

            /*
            The user tapped on a letter in the letter chooser. Let's select that letter.
             */
            if ((currentLetter === false) && 
                     (currentColumn !== false) &&
                     (currentChooserLetter == this.lastLetter)) {
                this.chooseLetterLayer.setBaseLetter(this.lastLetter);
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
                this.chooseLetterLayer.setBaseLetter(this.chooseLetterLayer.getBaseLetter());
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
        /*
        The user tapped on a letter in the current word after choosing a letter.
         */
        else if (this.sc.state == this.sc.states.CHANGING_LETTER_NODRAG) {
            this.finishWord();   
        }
        else if (this.sc.state == this.sc.states.GESTURING) {
            this.sc.IDLE();
        }
        else if (this.sc.state == this.sc.states.ERASING_WORD) {
            var vector = this.calculateVector(x,y),
                angle = vector.angle,
                distance = vector.distance,
                solutionLayer = this.solutionLayer;

            if (((Math.PI - Math.abs(angle)) <= 0.30) && 
                (distance > this.distanceThreshold)) {
                this.quatGame.getPuzzle().goBack();
                this.quatGame.saveToLocal();
                this.solutionLayer.updateFromModel(this.quatGame);
            }
                
            solutionLayer.currentWord.setOpacity(255);
            solutionLayer.prevWord.setOpacity(0);
            solutionLayer.prevWord.y = solutionLayer.currentWord.y + solutionLayer.fontSize;
            this.sc.IDLE();
        }
    }
});