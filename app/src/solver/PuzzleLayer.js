var quat = quat || {};
quat.solver = quat.solver || {};

quat.solver.PuzzleLayer = cc.Layer.extend({

    ctor: function(gameScene, gameBounds, fontSize, gameState) {
        this._super();

        this.gameScene = gameScene;
        this.gameBounds = gameBounds;
        this.fontSize = fontSize;
        this.quatGame = gameState;

        return true;
    },

    onEnter: function() {
        this._super();

        // Initialize the model and get a new puzzle
        var quatGame = this.quatGame;

        // Initialize our layers
        var gameBounds = this.gameBounds,
            fontSize = this.fontSize;

        // Has all of the indicators about the current solution and steps
        var solutionLayer = new quat.solver.SolutionLayer(this, gameBounds, fontSize);
        solutionLayer.zIndex = 2;
        this.addChild(solutionLayer);
        this.solutionLayer = solutionLayer;

        // Allows the user to choose letters with a slider
        var sliderLayer = new quat.solver.SliderLayer(gameBounds, solutionLayer.currentWord, fontSize);
        this.addChild(sliderLayer);
        sliderLayer.setVisible(false);
        sliderLayer.zIndex = 3;
        this.sliderLayer = sliderLayer;

        // Allows the user to choose letters with a keyboard
        var keyboardLayer = new quat.solver.KeyboardLayer(gameBounds);
        this.addChild(keyboardLayer);
        keyboardLayer.setVisible(false);
        keyboardLayer.zIndex = 3;
        this.keyboardLayer = keyboardLayer;

        // Used to show the pings that happen then the user finished a puzzle
        var finishedLayer = new quat.solver.FinishedLayer(fontSize, gameBounds);
        this.addChild(finishedLayer);
        this.finishedLayer = finishedLayer;

        // Used for notifications that need the user's attention
        var textIndicatorLayer = new quat.solver.TextIndicatorLayer(fontSize, gameBounds);
        textIndicatorLayer.zIndex = 3;
        this.addChild(textIndicatorLayer);
        this.textIndicatorLayer = textIndicatorLayer;

        this._slider = false;

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
                x: event.getLocationX(),
                y: event.getLocationY()
            };
        };

        // Touch listener
        var trackingTouch = false,
            layer = this;

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: false,
            onTouchBegan: function(event) {
                if (!layer.isVisible()) {
                    return false;
                }

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

    applyTheme: function(theme) {
        this.solutionLayer.applyTheme(theme);
        this.sliderLayer.applyTheme(theme);
        this.keyboardLayer.applyTheme(theme);
        this.finishedLayer.applyTheme(theme);
        this.textIndicatorLayer.applyTheme(theme);
    },

    setOpacity: function(opacity) {
        this.solutionLayer.setOpacity(opacity);
        this.sliderLayer.setOpacity(opacity);
        this.keyboardLayer.setOpacity(opacity);
        this.textIndicatorLayer.setOpacity(opacity);
    }
});

