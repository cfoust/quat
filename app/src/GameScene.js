var quat = quat || {};

quat.GameScene = cc.Scene.extend({
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

        // Generate the bounds used by all internal layers
        var gameBounds = this.calculateSize();

        // Add the universal background layer
        this.backgroundLayer = new quat.BackgroundLayer();
        this.addChild(this.backgroundLayer);

        // Calculate the global font sizes
        var fontSize = gameBounds.width * 0.18,
            smallFontSize = fontSize * .5;

        // Create a reference to the puzzle layer
        this.puzzleLayer = new quat.solver.PuzzleLayer(gameBounds, fontSize);
        this.addChild(this.puzzleLayer);

        // Create a reference to the puzzle layer
        this.menuLayer = new quat.menu.MenuLayer(gameBounds, fontSize);
        this.addChild(this.menuLayer);

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

        // Handles states related to the capturing of game-wide gestures
        this.GSC = new quat.GameStateController(this);
        // Handles the state of the UI as a whole (like whether the user is
        // in a menu or playing)
        this.SSC = new quat.ScreenStateController(this);

        // Initialize the input manager for touches/clicks
        var touchInputManager = new quat.GameTouchInputManager(this, gameBounds.width);
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
