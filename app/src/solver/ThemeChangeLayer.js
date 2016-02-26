var quat = quat || {};
quat.solver = quat.solver || {};


quat.solver.ThemeChangeLayer = cc.Layer.extend({
    ctor:function (puzzleLayer, fontSize, gameBounds) {
        this._super();

        this.puzzleLayer = puzzleLayer;
        this.quatGame = puzzleLayer.quatGame;
        this.fontSize = fontSize;
        this.gameBounds = gameBounds;

        return true;
    },

    onEnter: function() {
        this._super();

        var fontSize = this.fontSize,
            gameBounds = this.gameBounds;

        var buttonHeight = fontSize * 1.3,
            buttonWidth = gameBounds.width / 2;

        var prevCallback = function() {
            console.log("PREV");
        };
        var prevButton = new quat.menu.Button("PREV", this.fontSize, buttonWidth, buttonHeight, prevCallback);
        prevButton.x = gameBounds.x;
        prevButton.y = gameBounds.height - buttonHeight;
        this.addChild(prevButton);
        this.prevButton = prevButton;

        var nextCallback = function() {
            console.log("NEXT");
        };
        var nextButton = new quat.menu.Button("NEXT", this.fontSize, buttonWidth, buttonHeight, nextCallback);
        nextButton.x = gameBounds.x + buttonWidth;
        nextButton.y = gameBounds.height - buttonHeight;
        this.addChild(nextButton);
        this.nextButton = nextButton;

        var selectCallback = function() {
            console.log("SELECT");
        };
        var selectedButton = new quat.menu.Button("SELECT", this.fontSize, gameBounds.width, buttonHeight, selectCallback);
        selectedButton.x = gameBounds.x;
        selectedButton.y = gameBounds.height - (buttonHeight*2);
        this.addChild(selectedButton);
        this.selectedButton = selectedButton;
    },

    setVisible: function(visible) {
        this.nextButton.setVisible(visible);
        this.prevButton.setVisible(visible);
        this.selectedButton.setVisible(visible);
    },

    applyTheme: function(theme) {
        this.nextButton.applyTheme(theme);
        this.prevButton.applyTheme(theme);
        this.selectedButton.applyTheme(theme);
    },

    setOpacity: function(opacity) {
        this.nextButton.setOpacity(opacity);
        this.prevButton.setOpacity(opacity);
        this.selectedButton.setOpacity(opacity);
    },
});