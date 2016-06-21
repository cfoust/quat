var quat = quat || {};
quat.solver = quat.solver || {};

/**
 * Handles keyboard inputs for the PuzzleScene class. Transitions
 * from state to state and manipulates the game based on user input.
 */
quat.solver.KeyboardInputManager = function(puzzleScene) {
	// Grab all the references to things we need from puzzleScene
	this.quatGame = puzzleScene.quatGame;
	this.puzzleLayer = this;
    this.solutionLayer = puzzleScene.solutionLayer;
    this.sliderLayer = puzzleScene.sliderLayer;
    this.sc = puzzleScene.stateController;
    this.textIndicatorLayer = puzzleScene.textIndicatorLayer;

    // Used to track the last column the user had clicked in
    this.lastColumn = -1;
};

quat.solver.KeyboardInputManager.prototype.inputKeycode = function(keyCode) {
	var key = String.fromCharCode(keyCode);

	// If key is a number string
	if (!isNaN(key)) {
	    // It is, so convert it into a number
	    var number = +key;

	    if ((number < 1) || (number > 4)) {
	    	this.sc.IDLE();
	    	return;
	    }

	    // Shift the number down one to match the indexes of letters
	    number -= 1;

	    // Set the last
	    this.lastColumn = number;

	    this.sc.CHOOSING_LETTER(number);

	    this.sc.CHANGING_LETTER_NODRAG();

	    return;
	}

	// Try to understand they key as a letter
	var letterCode = (key.charCodeAt(0) - 65);

	/* 
	If we have a letter chooser open and the user enters a letter
	of the alphabet.
	*/ 
	if ((this.sc.state == this.sc.states.CHANGING_LETTER_NODRAG) && 
	    (letterCode < 26) &&
	    (letterCode >= 0)) {

	    var puzzle = this.quatGame.getPuzzle(),
			oldWord = puzzle.getCurrentWord(),
	        newWord = oldWord.substr(0,this.lastColumn) + key + oldWord.substr(this.lastColumn + 1);

	    newWord = newWord.toLowerCase();

	    // Grab some references to the current game and puzzle
        var quatGame = this.quatGame;

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

	    this.sc.IDLE();
	}
	// If the user enters a backspace while the letter chooser
	// is shown, hide the letter chooser
	else if ((this.sc.state == this.sc.states.CHANGING_LETTER_NODRAG) &&
	         (keyCode == 8)) {
	    this.sc.IDLE();
	}
	// If user enters up on the arrow pad while the 
	// letter chooser is shown, scroll up
	else if ((this.sc.state == this.sc.states.CHANGING_LETTER_NODRAG) &&
	         (keyCode == 38)) {
	    this.sliderLayer.shift(1);
	}
	// If user enters down on the arrow pad while the 
	// letter chooser is shown, scroll down
	else if ((this.sc.state == this.sc.states.CHANGING_LETTER_NODRAG) &&
	         (keyCode == 40)) {
	    this.sliderLayer.shift(-1);
	}
	// If the user enters a backspace while idle, see if we
	// can remove one of the last words
	else if ((this.sc.state == this.sc.states.IDLE) &&
	         (keyCode == 8)) {
	    this.quatGame.getPuzzle().goBack();
		this.quatGame.saveToLocal();
	    this.sc.IDLE();
	}

	// todo: enable arrow key support for manipulating letter chooser
};