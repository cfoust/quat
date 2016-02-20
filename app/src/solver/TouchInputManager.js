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
    this.chooseLetterLayer = puzzleScene.chooseLetterLayer;
    this.sc = puzzleScene.stateController;

    // Used to track the last column the user had clicked in
    this.lastColumn = -1;

    // Records the last location the user started touching or clicking
    this.lastMouseDown = {};

    // Records the previous y offset of the last drag action
    this.previousOffset = 0;
}

quat.solver.TouchInputManager.prototype.inputBegan = function(x, y) {
	this.lastMouseDown = {x: x, y: y};

    if (this.sc.state == this.sc.states.IDLE) {
        // Check to see if this is a click in the current word
        var currentLetter = this.solutionLayer.pointInCurrentWord(x,y);

        if (currentLetter !== false) {
            this.lastColumn = currentLetter;
            this.sc.CHOOSING_LETTER(currentLetter);
        }
    }
    else if (this.sc.state == this.sc.states.CHANGING_LETTER_NODRAG) {
        var currentColumn = this.solutionLayer.pointInColumn(x,y);

        if ((currentColumn === false) || (currentColumn != this.lastColumn)) {
            this.sc.IDLE();
        }
        else {
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
    if (this.sc.state == this.sc.states.CHOOSING_LETTER) {
    	this.sc.IDLE();
    }
    /*
    The user stopped dragging after starting to move the letter chooser.
     */
    else if (this.sc.state == this.sc.states.CHANGING_LETTER_DRAG) {
        var currentLetter = this.solutionLayer.pointInCurrentWord(x,y);
        var currentColumn = this.solutionLayer.pointInColumn(x,y);

        /*
        The user stopped dragging outside of a letter, so we keep the letter
        chooser up and let them keep manipulating it.
         */
        if ((currentLetter === false) && (currentColumn !== false)) {
        	// Resets the base letter to the current letter. 
        	// This looks nonsensical, but it's a problem of method naming more
        	// than anything. The getBaseLetter() method returns the CURRENT
        	// letter at the bottom instead of the REAL base letter before any
        	// offset.
            this.chooseLetterLayer.setBaseLetter(this.chooseLetterLayer.getBaseLetter());
            this.sc.CHANGING_LETTER_NODRAG();
        /*
        The user stopped dragging or touched inside a letter after selecting a 
        letter with the letter chooser, so we enter their choice.
         */
        } else if ((currentLetter === this.lastColumn) && (currentColumn == this.lastColumn)) {
            this.finishWord();
        }
    }
    /*
    The user tapped on a letter in the current word after choosing a letter.
     */
    else if (this.sc.state == this.sc.states.CHANGING_LETTER_NODRAG) {
        this.finishWord();   
    }
};