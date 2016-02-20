var quat = quat || {};
quat.solver = quat.solver || {};

/**
 * Handles all transitions between states.
 */
quat.solver.StateController = function(puzzleScene) {
	// Grab all the references to things we need from puzzleScene
	this.quatGame = puzzleScene.quatGame;
	this.backgroundLayer = puzzleScene.backgroundLayer;
    this.solutionLayer = puzzleScene.solutionLayer;
    this.chooseLetterLayer = puzzleScene.chooseLetterLayer;
    this.solutionSize = puzzleScene.solutionSize;

    // The enumeration of all possible states for the solver GUI.
    this.states = {
        /*
        When only the current solution progress is showing.
         */
        IDLE: 0,
        /*
        When the user clicked on one of the letters in the current word,
        but has not dragged out of the current word yet.
         */
        CHOOSING_LETTER: 1,
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
    };


    // Sets the current state to IDLE
    this.state = this.states.IDLE;

    // Records the previous y offset of the last drag action
    this.previousOffset = 0;
}

quat.solver.StateController.prototype.IDLE = function() {
	if ((this.state == this.states.CHANGING_LETTER_NODRAG) ||
		(this.state == this.states.CHOOSING_LETTER)) {
		this.chooseLetterLayer.setVisible(false);
	}

	this.state = this.states.IDLE;
};

quat.solver.StateController.prototype.CHOOSING_LETTER = function(column) {
	// Move the letter chooser to its proper location
	this.chooseLetterLayer.x = (column * (this.solutionSize.width / 4)) + this.solutionSize.x;
    this.chooseLetterLayer.setBaseLetter(this.quatGame.getCurrentWord()[column]);
    this.chooseLetterLayer.setVisible(true);

	this.state = this.states.CHOOSING_LETTER;
};


quat.solver.StateController.prototype.CHANGING_LETTER_DRAG = function() {
	this.state = this.states.CHANGING_LETTER_DRAG;
};

quat.solver.StateController.prototype.CHANGING_LETTER_NODRAG = function() {
	this.state = this.states.CHANGING_LETTER_NODRAG;
};