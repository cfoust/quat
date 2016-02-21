var quat = quat || {};
quat.solver = quat.solver || {};

/**
 * Handles coordinate-based inputs for the PuzzleScene class. Transitions
 * from state to state and manipulates the game based on user input.
 */
quat.solver.TouchInputManager = function(puzzleScene) {
	// Grab all the references to things we need from puzzleScene
	this.quatGame = puzzleScene.quatGame;
    this.solutionLayer = puzzleScene.solutionLayer;
    this.solutionSize = puzzleScene.solutionSize;
    this.chooseLetterLayer = puzzleScene.chooseLetterLayer;
    this.sc = puzzleScene.stateController;

    // Used to track the last column the user had clicked in
    this.lastColumn = -1;

    this.lastLetter = "";

    // Records the last location the user started touching or clicking
    this.lastMouseDown = {};

    // Records the previous y offset of the last drag action
    this.previousOffset = 0;

    this.gestureThreshold = this.solutionSize.width * 0.03;
    this.distanceThreshold = this.solutionSize.width * 0.61;
}

quat.solver.TouchInputManager.prototype.inputBegan = function(x, y) {
	this.lastMouseDown = {x: x, y: y};

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
};

quat.solver.TouchInputManager.prototype.inputMoved = function(x, y) {
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
                var offset = y - this.lastMouseDown.y;
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
        var offset = y - this.lastMouseDown.y;
        this.chooseLetterLayer.setOffset(offset);
    }
    else if (this.sc.state == this.sc.states.GESTURING) {
        var xDelta = x -this.lastMouseDown.x,
            yDelta = y - this.lastMouseDown.y,
            distance = Math.sqrt(Math.pow(xDelta,2) + Math.pow(yDelta,2)),
            angle = Math.atan2(yDelta, xDelta);
        
        if (((Math.PI - Math.abs(angle)) <= 0.30) &&
            (distance > this.gestureThreshold) &&
            (this.quatGame.getCurrentSteps().length > 1)) {
            this.sc.ERASING_WORD();
        }
    }
    else if (this.sc.state == this.sc.states.ERASING_WORD) {
        var xDelta = x -this.lastMouseDown.x,
            yDelta = y - this.lastMouseDown.y,
            distance = Math.sqrt(Math.pow(xDelta,2) + Math.pow(yDelta,2)),
            angle = Math.atan2(yDelta, xDelta);

        if ((Math.PI - Math.abs(angle)) <= 0.30) {
            if (distance > this.distanceThreshold) {
                this.quatGame.goBack();
                this.solutionLayer.updateSolution(this.quatGame.getCurrentSteps());
                this.lastMouseDown = {x: x, y: y};
                this.sc.GESTURING();
            } 
            else {
                var percent = (this.distanceThreshold - distance) / this.distanceThreshold;
                percent = percent * 255;
                this.solutionLayer.setCurrentOpacity(percent);
            }
        } else {
            this.solutionLayer.setCurrentOpacity(255);
            this.sc.GESTURING();
        }
    }
};

quat.solver.TouchInputManager.prototype.finishWord = function() {
	this.sc.state = this.sc.states.IDLE;
    this.chooseLetterLayer.setVisible(false);

    var oldWord = this.quatGame.getCurrentWord(),
        newWord = oldWord.substr(0,this.lastColumn) + this.chooseLetterLayer.getBaseLetter() + oldWord.substr(this.lastColumn + 1);

    newWord = newWord.toLowerCase();

    var result = this.quatGame.addWord(newWord);
    if (result) {
        if (this.quatGame.atGoal()) {
            this.quatGame.newPuzzle();
            this.solutionLayer.updateGoal(this.quatGame.getGoal());
        }
        this.solutionLayer.updateSolution(this.quatGame.getCurrentSteps());
    } else {
        console.log(newWord + " is not a word");
    }
};

quat.solver.TouchInputManager.prototype.inputDone = function(x, y) {
	/*
	The user slid along the current word to bring up the letter choosers, but
	never dragged upwards to start changing a letter. We just hide the chooser.
	 */
    // if (this.sc.state == this.sc.states.CHOOSING_LETTER) {
    // 	this.sc.IDLE();
    // }
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
        this.solutionLayer.setCurrentOpacity(255);
        this.sc.IDLE();
    }
};