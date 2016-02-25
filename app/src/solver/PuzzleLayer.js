var quat = quat || {};
quat.solver = quat.solver || {};

quat.solver.PuzzleLayer = cc.Layer.extend({
    ctor: function(gameBounds, fontSize) {
        this._super();

        this.gameBounds = gameBounds;
        this.fontSize = fontSize;

        return true;
    },

    onEnter: function() {
        this._super();

        // Initialize the model and get a new puzzle
        var quatGame = new quat.GameInfo();
        this.quatGame = quatGame;
        quatGame.newPuzzle();

        // Initialize our layers
        var gameBounds = this.gameBounds,
            fontSize = this.fontSize,
            solutionLayer = new quat.solver.SolutionLayer(gameBounds.width, 
                                              gameBounds.height,
                                              fontSize),
            chooseLetterLayer = new quat.solver.ChooseLetterLayer(
                                              gameBounds.width / 4,
                                              gameBounds.height,
                                              fontSize),
            textIndicatorLayer = new quat.solver.TextIndicatorLayer(fontSize,
                                              gameBounds,
                                              this.windowWidth,
                                              this.windowHeight);
        textIndicatorLayer.x = 0;
        textIndicatorLayer.y = 0;
        textIndicatorLayer.zIndex = 1;

        chooseLetterLayer.setVisible(false);

        // Sets the solution layer to have its calculated bounds
        solutionLayer.x = gameBounds.x;
        solutionLayer.y = gameBounds.y;
        solutionLayer.zIndex = 2;

        chooseLetterLayer.x = gameBounds.x;
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
        this.gameBounds = gameBounds;

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
                x: event.getLocationX() - gameBounds.x,
                y: event.getLocationY() - gameBounds.y
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

