var quat = quat || {};

/*
You'll notice that this is remarkably similar to the SolverStateController.

They are very similar in implementation, but right now I don't know what method
of JavaScript class inheritance I want to use.
 */

quat.GameStateController = quat.StateController.extend({
    states: {
        /*
        When only the current solution progress is showing.
         */
        IDLE: null,

        GESTURING: null,
        /*
        The user has started swiping to the right to get to the main menu.
         */
        SWIPING_TO_MENU: null
    },

    init: function(gameScene) {
        this._super();
        
        this.puzzleScene = gameScene.puzzleScene;
    }
});