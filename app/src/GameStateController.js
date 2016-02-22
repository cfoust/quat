var quat = quat || {};

/*
You'll notice that this is remarkably similar to the SolverStateController.

They are very similar in implementation, but right now I don't know what method
of JavaScript class inheritance I want to use.
 */

/**
 * Handles all transitions between states.
 */
quat.GameStateController = function(gameScene) {
	// Grab all the references to things we need from puzzleScene
	this.puzzleScene = gameScene.puzzleScene;

    // The enumeration of all possible states for the solver GUI.
    this.states = {
        /*
        When only the current solution progress is showing.
         */
        IDLE: 0,

        GESTURING: 1,
        /*
        The user has started swiping to the right to get to the main menu.
         */
        SWIPING_TO_MENU: 2
    };


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

quat.GameStateController.prototype.IDLE = function() {
	this.setState(this.states.IDLE);
};

quat.GameStateController.prototype.GESTURING = function() {
	this.setState(this.states.GESTURING);
};

quat.GameStateController.prototype.SWIPING_TO_MENU = function() {
    this.setState(this.states.SWIPING_TO_MENU);
};