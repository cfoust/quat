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

    setThemeChange: function(set) {
        this._changingTheme = set;
        if (set) {
            this.touchInputManager.setEnabled(false);
            this.textIndicatorLayer.clearMessages();
            this.textIndicatorLayer.addMessage('Swipe from left to right to return to the main menu. Each theme comes with special puzzles.'.toUpperCase(), true);

            var solutionLayer = this.solutionLayer;
            solutionLayer.goalWord.changeWord("WORD");
            solutionLayer.currentWord.setVisible(false);
            solutionLayer.stepsWord.setVisible(false);
            this.themeChangeLayer.setVisible(true);
        }
        else {
            this.touchInputManager.setEnabled(true);
            this.themeChangeLayer.setVisible(false);

            var solutionLayer = this.solutionLayer;
            solutionLayer.currentWord.setVisible(true);
            solutionLayer.stepsWord.setVisible(true);
            solutionLayer.updateFromModel(this.quatGame);
        }
    },

    onEnter: function() {
        this._super();



        // Initialize the model and get a new puzzle
        var quatGame = this.quatGame;

        // Initialize our layers
        var gameBounds = this.gameBounds,
            fontSize = this.fontSize;

        // Has all of the indicators about the current solution and steps
        var solutionLayer = new quat.solver.SolutionLayer(gameBounds.width, gameBounds.height, fontSize);
        solutionLayer.x = gameBounds.x;
        solutionLayer.y = gameBounds.y;
        solutionLayer.zIndex = 2;
        this.addChild(solutionLayer);
        this.solutionLayer = solutionLayer;

        // Allows the user to choose letters
        var chooseLetterLayer = new quat.solver.ChooseLetterLayer(gameBounds.width / 4, gameBounds.height, fontSize);
        this.addChild(chooseLetterLayer);
        chooseLetterLayer.setVisible(false);
        chooseLetterLayer.x = gameBounds.x;
        chooseLetterLayer.y = solutionLayer.panelHeight;
        chooseLetterLayer.zIndex = 3;
        this.chooseLetterLayer = chooseLetterLayer;

        // Used for notifications that need the user's attention
        var textIndicatorLayer = new quat.solver.TextIndicatorLayer(fontSize, gameBounds);
        textIndicatorLayer.x = 0;
        textIndicatorLayer.y = 0;
        textIndicatorLayer.zIndex = 1;
        this.addChild(textIndicatorLayer);
        this.textIndicatorLayer = textIndicatorLayer;

        var themeChangeLayer = new quat.solver.ThemeChangeLayer(this, fontSize, gameBounds);
        themeChangeLayer.x = 0;
        themeChangeLayer.y = 0;
        themeChangeLayer.zIndex = 2;
        this.addChild(themeChangeLayer);
        themeChangeLayer.setVisible(false);
        this.themeChangeLayer = themeChangeLayer;
        this._changingTheme = false;

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
        this.themeChangeLayer.applyTheme(theme);
        this.chooseLetterLayer.applyTheme(theme);
        this.textIndicatorLayer.applyTheme(theme);
    },

    setOpacity: function(opacity) {
        this.solutionLayer.setOpacity(opacity);
        this.chooseLetterLayer.setOpacity(opacity);
        this.textIndicatorLayer.setOpacity(opacity);
        this.themeChangeLayer.setOpacity(opacity);
    }
});

