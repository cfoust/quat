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
        this.solutionSize = puzzleLayer.solutionSize;
        this.chooseLetterLayer = puzzleLayer.chooseLetterLayer;
        this.textIndicatorLayer = puzzleLayer.textIndicatorLayer;
        this.sc = puzzleLayer.stateController;

        // Used to track the last column the user had clicked in
        this.lastColumn = -1;

        this.lastLetter = "";

        // Records the previous y offset of the last drag action
        this.previousOffset = 0;

        this.gestureThreshold = this.solutionSize.width * 0.03;
        this.distanceThreshold = this.solutionSize.width * 0.61;
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
                (this.quatGame.getCurrentSteps().length > 1)) {
                this.sc.ERASING_WORD();
            }
        }
        else if (this.sc.state == this.sc.states.ERASING_WORD) {
            var vector = this.calculateVector(x,y),
                angle = vector.angle,
                distance = vector.distance;

            // The user is dragging and has maintained the strict right-to-left
            // angle. They have to stay within 0.3 radians the whole time
            if ((Math.PI - Math.abs(angle)) <= 0.30) {
                var percent = (this.distanceThreshold - distance) / this.distanceThreshold;

                percent = Math.min((percent * 255) + 30, 255);
                this.solutionLayer.setCurrentWordOpacity(percent);
            // Looks like they decided otherwise, stop tracking this touch
            } else {
                this.solutionLayer.setCurrentWordOpacity(255);
                this.sc.GESTURING();
            }
        }
    },

    finishWord: function() {
        this.sc.state = this.sc.states.IDLE;
        this.chooseLetterLayer.setVisible(false);

        var oldWord = this.quatGame.getCurrentWord(),
            newWord = oldWord.substr(0,this.lastColumn) + this.chooseLetterLayer.getBaseLetter() + oldWord.substr(this.lastColumn + 1);

        newWord = newWord.toLowerCase();

        var result = this.quatGame.addWord(newWord);
        if (result) {
            if (this.quatGame.atGoal()) {
                var par = this.quatGame.getPar(),
                    steps = this.quatGame.getCurrentSteps().length - 1,
                    points = this.quatGame.pointsAdded;
                if (par == steps) {
                    this.textIndicatorLayer.longIn("MADE PAR!\n+" + points.toString());
                } else {
                    this.textIndicatorLayer.longIn("+" +  + points.toString());
                }
                this.quatGame.newPuzzle();
            }
            this.solutionLayer.updateFromModel(this.quatGame);
        } else {
            if (newWord != oldWord) {
                this.textIndicatorLayer.longIn(newWord.toUpperCase() + " IS NOT A WORD");
            }
        }
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
                distance = vector.distance;

            if (((Math.PI - Math.abs(angle)) <= 0.30) && 
                (distance > this.distanceThreshold)) {
                this.quatGame.goBack();
                this.solutionLayer.updateFromModel(this.quatGame);
            } else {
                this.solutionLayer.setCurrentWordOpacity(255);
                
            }
            this.sc.IDLE();
        }
    }
});