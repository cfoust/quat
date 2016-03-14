var quat = quat || {};

/**
 * Handles coordinate-based inputs for the gameScene class. Transitions
 * from state to state and manipulates the game based on user input.
 */
quat.GameTouchInputManager = quat.TouchInputManager.extend({
    init: function(gameScene, baseWidth) {
        this._super();

        this.gameScene = gameScene; 
        this.puzzleLayer = gameScene.puzzleLayer;
        this.menuLayer = gameScene.menuLayer;
        this.statsLayer = gameScene.statsLayer;
        this.titleWord = gameScene.titleWord;
        this.subtextWord = gameScene.subtextWord;
        this.GSC = gameScene.GSC;
        this.SSC = gameScene.SSC;

        this.gestureThreshold = baseWidth * 0.03;
        this.distanceThreshold = baseWidth * 0.61;
    },

    began: function(x, y) {
        if ((this.GSC.state == this.GSC.states.IDLE) &&
            (y > this.puzzleLayer.solutionLayer.topOfCurrentWord())) {
            this.GSC.GESTURING();
        }
    },

    moved: function(x, y) {
        if (this.SSC.state == this.SSC.states.MAIN_MENU) {
            return;
        }
        /*
         The user is choosing the letter they want to change.
        */
        if (this.GSC.state == this.GSC.states.GESTURING) {
            var vector = this.calculateVector(x,y),
                angle = vector.angle,
                distance = vector.distance;
        }
    },

    done: function(x, y) {
        if (this.GSC.state == this.GSC.states.GESTURING) {
            this.GSC.IDLE();
        }
    }
});