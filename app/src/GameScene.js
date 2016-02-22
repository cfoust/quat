var quat = quat || {};

quat.GameScene = cc.Scene.extend({
    ctor: function(windowWidth, windowHeight) {
        this._super();

        this.windowWidth = windowWidth;
        this.windowHeight = windowHeight;

        return true;
    },
    onEnter: function() {
        this._super();

        // Add the universal background layer
        this.backgroundLayer = new quat.BackgroundLayer();
        this.addChild(this.backgroundLayer);

        // Create a reference to the puzzle scene
        this.puzzleLayer = new quat.solver.PuzzleLayer(this.windowWidth, this.windowHeight);
        this.addChild(this.puzzleLayer);

        // Create the MENU word
        var menuWord = new cc.LabelTTF("MENU", "Arial", this.puzzleLayer.solutionLayer.fontSize);
        menuWord.x = this.windowWidth / 2;
        menuWord.y = this.windowHeight / 2;
        menuWord.setOpacity(0);
        this.addChild(menuWord);
        this.menuWord = menuWord;

        this.stateController = new quat.GameStateController(this);

        // Initialize the input manager for touches/clicks
        var touchInputManager = new quat.TouchInputManager(this, this.puzzleLayer.solutionSize.width);
        this.touchInputManager = touchInputManager;

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
                var x = event.getLocationX(),
                    y = event.getLocationY();
                
                touchInputManager.inputBegan(x, y);

                return true;
            },
            onTouchMoved: function(event){
                var x = event.getLocationX(),
                    y = event.getLocationY();
                touchInputManager.inputMoved(x, y);
                return true;
            },
            onTouchEnded: function(event){
                var x = event.getLocationX(),
                    y = event.getLocationY();
                touchInputManager.inputDone(x, y);
                trackingTouch = false;
                return true;
            }
        },this);
    }
});
