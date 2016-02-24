var quat = quat || {};
quat.solver = quat.solver || {};

quat.solver.PuzzleLayer = cc.Layer.extend({
    ctor: function(windowWidth, windowHeight) {
        this._super();

        this.windowWidth = windowWidth;
        this.windowHeight = windowHeight;

        return true;
    },

    /**
     * Calculates the size of the playing area based on the real resolution.
     *
     * Essentially, we can just fill the rest of the canvas up with the
     * background.
     * 
     * @return {Object} Object with 'width', 'height', 'x', and 'y'.
     */
    calculateSize: function() {
        var w = this.windowWidth,
            h = this.windowHeight,
            cWidth = 0, // The calculated width
            cHeight = h, // The calculated height (always h)
            cX = 0, // The calculated X
            cY = 0; // The calculated Y (always 0)

        var NICE_WIDTH = 300;

        // Case 1: Landscape (and square) orientation
        if ((w >= h) || ((w < h) && (w > NICE_WIDTH))) {
            cWidth = Math.min(w, NICE_WIDTH);
            cX = (w / 2) - (cWidth / 2);
        // Case 2: Portrait orientation
        } else {
            cWidth = w;
            cX = 0;
        }

        return {
            width: cWidth,
            height: cHeight,
            x: cX,
            y: cY
        };
    },

    onEnter: function() {
        this._super();

        // Initialize the model and get a new puzzle
        var quatGame = new quat.GameInfo();
        this.quatGame = quatGame;
        quatGame.newPuzzle();

        // Initialize our layers
        var solutionSize = this.calculateSize(),
            // fontSize = solutionSize.width * 0.18,
            fontSize = solutionSize.width * 0.18,
            solutionLayer = new quat.solver.SolutionLayer(solutionSize.width, 
                                              solutionSize.height,
                                              fontSize),
            chooseLetterLayer = new quat.solver.ChooseLetterLayer(
                                              solutionSize.width / 4,
                                              solutionSize.height,
                                              fontSize),
            textIndicatorLayer = new quat.solver.TextIndicatorLayer(fontSize,
                                              solutionSize,
                                              this.windowWidth,
                                              this.windowHeight);
        textIndicatorLayer.x = 0;
        textIndicatorLayer.y = 0;
        textIndicatorLayer.zIndex = 1;

        chooseLetterLayer.setBaseLetter('D');
        chooseLetterLayer.setVisible(false);

        // Sets the solution layer to have its calculated bounds
        solutionLayer.x = solutionSize.x;
        solutionLayer.y = solutionSize.y;
        solutionLayer.zIndex = 2;

        chooseLetterLayer.x = solutionSize.x;
        chooseLetterLayer.y = solutionLayer.panelHeight;
        chooseLetterLayer.zIndex = 3;


        // Add each layer to this rendering target
        this.addChild(solutionLayer);
        this.addChild(chooseLetterLayer);
        this.addChild(textIndicatorLayer);

        // Have them be accessible from other methods
        this.solutionLayer = solutionLayer;
        this.chooseLetterLayer = chooseLetterLayer;
        this.textIndicatorLayer = textIndicatorLayer;
        this.solutionSize = solutionSize;

        // Update the solution layer's current status and goal
        solutionLayer.updateFromModel(quatGame);

        // Initialize the state controller for GUI state handling
        var stateController = new quat.solver.SolverStateController(this);
        this.stateController = stateController;

        // Initialize the input manager for touches/clicks
        var touchInputManager = new quat.solver.SolverTouchInputManager(this);
        this.touchInputManager = touchInputManager;

        // Initialize the input manager for key presses
        var keyInputManager = new quat.solver.KeyboardInputManager(this);
        this.keyInputManager = keyInputManager;

        /**
         * Takes in a mouse (or touch) event and transposes it into
         * solution space.
         * @param  {Event} event Mouse or touch event with x and y coordinates.
         * @return {Object}       Object containing 'x' and 'y' fields that
         *                        have been moved to be in solutionLayer
         *                        space.
         */
        var transpose = function(event) {
            return {
                x: event.getLocationX() - solutionSize.x,
                y: event.getLocationY() - solutionSize.y
            };
        };

        // Touch listener
        var trackingTouch = false;
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: false,
            onTouchBegan: function(event) {
                if (trackingTouch) {
                    return false;
                } else {
                    trackingTouch = true;
                }
                
                var coords = transpose(event);
                touchInputManager.inputBegan(coords.x, coords.y);

                return true;
            },
            onTouchMoved: function(event){
                var coords = transpose(event);
                touchInputManager.inputMoved(coords.x, coords.y);
                return true;
            },
            onTouchEnded: function(event){

                var coords = transpose(event);
                touchInputManager.inputDone(coords.x, coords.y);
                trackingTouch = false;
                return true;
            }
        },this);

        cc.eventManager.addListener({
            event: cc.EventListener.KEYBOARD,
            onKeyReleased: function(keyCode, event){
                keyInputManager.inputKeycode(keyCode);
            }
        }, this);

    },

    setOpacity: function(opacity) {
        this.solutionLayer.setOpacity(opacity);
        this.chooseLetterLayer.setOpacity(opacity);
        this.textIndicatorLayer.setOpacity(opacity);
    }
});

