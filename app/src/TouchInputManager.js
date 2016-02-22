var quat = quat || {};

/**
 * Handles coordinate-based inputs for the gameScene class. Transitions
 * from state to state and manipulates the game based on user input.
 */
quat.TouchInputManager = function(gameScene, baseWidth) {
	// Grab all the references to things we need from gameScene
    this.gameScene = gameScene; 
    this.puzzleLayer = gameScene.puzzleLayer;
    this.menuWord = gameScene.menuWord;
    this.sc = gameScene.stateController;

    // Records the last location the user started touching or clicking
    this.lastMouseDown = {};

    this.gestureThreshold = baseWidth * 0.03;
    this.distanceThreshold = baseWidth * 0.61;

    /**
     * Calculates the angle and distance of from the last mouse down to the
     * given point.
     * @param  {number} x x coordinate
     * @param  {number} y y coordinate
     * @return {Object} Object with 'angle' and 'distance' fields.
     */
    this.calculateVector = function(x,y) {
        var xDelta = x -this.lastMouseDown.x,
            yDelta = y - this.lastMouseDown.y,
            distance = Math.sqrt(Math.pow(xDelta,2) + Math.pow(yDelta,2)),
            angle = Math.atan2(yDelta, xDelta);

        return {distance: distance, angle: angle};
    }
}

quat.TouchInputManager.prototype.inputBegan = function(x, y) {
	this.lastMouseDown = {x: x, y: y};

    if (this.sc.state == this.sc.states.IDLE) {
        this.sc.GESTURING();
    }
};

quat.TouchInputManager.prototype.inputMoved = function(x, y) {
	/*
	The user is choosing the letter they want to change.
	 */
	if (this.sc.state == this.sc.states.GESTURING) {
        var vector = this.calculateVector(x,y),
            angle = vector.angle,
            distance = vector.distance;

        // The user is dragging from left to right
        if ((Math.abs(angle) <= 0.30) &&
            (distance > this.gestureThreshold)) {
            this.sc.SWIPING_TO_MENU();
        }
    }
    else if (this.sc.state == this.sc.states.SWIPING_TO_MENU) {
        var vector = this.calculateVector(x,y),
            angle = vector.angle,
            distance = vector.distance;

        // The user is dragging and has maintained the strict left-to-right
        // angle. They have to stay within 0.3 radians the whole time
        if (Math.abs(angle) <= 0.30) {
            // Get the distance as a percentage of the threshold
            var percent = (this.distanceThreshold - distance) / this.distanceThreshold;

            // Put it into the range 0-255
            percent *= 255;
            
            // Set the menu word's opacity
            this.menuWord.setOpacity(Math.min(255 - percent, 255));

            // Normalize the puzzle layer's opacity
            percent = Math.min(percent + 30, 255);

            this.puzzleLayer.setOpacity(percent);
        // Looks like they decided otherwise, stop tracking this touch
        } else {
            this.menuWord.setOpacity(0);
            this.puzzleLayer.setOpacity(255);
            this.sc.GESTURING();
        }
    }
};

quat.TouchInputManager.prototype.inputDone = function(x, y) {
	if (this.sc.state == this.sc.states.GESTURING) {
        this.sc.IDLE();
    }
    else if (this.sc.state == this.sc.states.SWIPING_TO_MENU) {
        this.puzzleLayer.setOpacity(255);
        this.menuWord.setOpacity(0);
        this.sc.IDLE();
    }
};