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

        var fontSize = this.puzzleLayer.solutionLayer.fontSize,
            smallFontSize = fontSize * .5;

        // Create the MENU word
        var titleWord = new cc.LabelTTF("MENU?", "Ubuntu", fontSize);
        titleWord.x = this.windowWidth / 2;
        titleWord.y = this.windowHeight / 2;
        titleWord.setOpacity(0);
        this.addChild(titleWord);
        this.titleWord = titleWord;

        // Create the release word
        var subtextWord = new cc.LabelTTF("RELEASE", "Ubuntu", smallFontSize);
        subtextWord.x = this.windowWidth / 2;
        subtextWord.y = (this.windowHeight * .48) - smallFontSize;
        subtextWord.setOpacity(0);
        this.addChild(subtextWord);
        this.subtextWord = subtextWord;

        this.stateController = new quat.GameStateController(this);

        // Initialize the input manager for touches/clicks
        var touchInputManager = new quat.GameTouchInputManager(this, this.puzzleLayer.solutionSize.width);
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
