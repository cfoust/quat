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

            // The user is dragging from left to right
            if ((Math.abs(angle) <= 0.30) &&
                (distance > this.gestureThreshold)) {
                this.GSC.SWIPING_RIGHT();
                this.titleWord.setOpacity(0);
                this.subtextWord.setOpacity(0);
            }
        }
        else if (this.GSC.state == this.GSC.states.SWIPING_RIGHT) {
            var vector = this.calculateVector(x,y),
                angle = vector.angle,
                distance = vector.distance;

            if ((this.SSC.state == this.SSC.states.GAME) || 
               (this.SSC.state == this.SSC.states.LOOK)) {
                this.titleWord.string = "MENU?";
            }

            // The user is dragging and has maintained the strict left-to-right
            // angle. They have to stay within 0.3 radians the whole time
            if (Math.abs(angle) <= 0.30) {
                // Get the distance as a percentage of the threshold
                var percent = (this.distanceThreshold - distance) / this.distanceThreshold;

                // Put it into the range 0-255
                percent *= 255;
                
                // Set the menu word's opacity
                var titleOpacity = Math.min(255 - percent, 255);
                this.titleWord.setOpacity(titleOpacity);
                this.subtextWord.setOpacity(titleOpacity);

                if (distance >= this.distanceThreshold) {
                    this.subtextWord.string = "RELEASE";
                } else {
                    this.subtextWord.string = "KEEP DRAGGING";
                }

                // Normalize the puzzle layer's opacity
                percent = Math.min(percent + 30, 255);

                this.SSC.currentLayer.setOpacity(percent);
                
            // Looks like they decided otherwise, stop tracking this touch
            } else {
                this.titleWord.setOpacity(0);
                this.subtextWord.setOpacity(0);
                this.SSC.currentLayer.setOpacity(255);
                this.GSC.GESTURING();
            }
        }
    },

    done: function(x, y) {
        if (this.GSC.state == this.GSC.states.GESTURING) {
            this.GSC.IDLE();
        }
        else if (this.GSC.state == this.GSC.states.SWIPING_RIGHT) {
            var vector = this.calculateVector(x,y),
                angle = vector.angle,
                distance = vector.distance;

            if (distance >= this.distanceThreshold) {
                if ((this.SSC.state == this.SSC.states.GAME) ||
                    (this.SSC.state == this.SSC.states.LOOK) ||
                    (this.SSC.state == this.SSC.states.STATS)) {
                    this.SSC.MAIN_MENU();
                }
            }
            this.puzzleLayer.setOpacity(255);
            this.menuLayer.setOpacity(255);
            this.titleWord.setOpacity(0);
            this.subtextWord.setOpacity(0);
            this.GSC.IDLE();
        }
    }
});