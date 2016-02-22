var quat = quat || {};

/**
 * Handles coordinate-based inputs for the gameScene class. Transitions
 * from state to state and manipulates the game based on user input.
 */
quat.TouchInputManager = Class.extend({
    init: function() {
        // Records the last location the user started touching or clicking
        this.lastDown = {};

        this.enabled = true;
    },

    setEnabled: function(enabled) {
        this.enabled = enabled;
    },

    getEnabled: function() {
        return this.enabled;
    },

    /**
     * Calculates the angle and distance of from the last mouse down to the
     * given point.
     * @param  {number} x x coordinate
     * @param  {number} y y coordinate
     * @return {Object} Object with 'angle' and 'distance' fields.
     */
    calculateVector: function(x,y) {
        var xDelta = x - this.lastDown.x,
            yDelta = y - this.lastDown.y,
            distance = Math.sqrt(Math.pow(xDelta,2) + Math.pow(yDelta,2)),
            angle = Math.atan2(yDelta, xDelta);

        return {distance: distance, angle: angle};
    },

    inputBegan: function(x, y) {
        if (!this.getEnabled()) {
            return;
        }

        this.lastDown = {x: x, y: y};
        this.began(x, y);
    },

    inputMoved: function(x,y) {
        if (!this.getEnabled()) {
            return;
        }
        this.moved(x, y);
    },

    inputDone: function(x,y) {
        if (!this.getEnabled()) {
            return;
        }
        this.done(x, y);
    },

    began: function(x, y) {},
    moved: function(x, y) {},
    done: function(x, y) {}
});
