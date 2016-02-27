var quat = quat || {};
quat.solver = quat.solver || {};


quat.solver.ThemeChangeLayer = cc.Layer.extend({

    ctor:function (puzzleLayer, fontSize, gameBounds) {
        this._super();

        this.puzzleLayer = puzzleLayer;
        this.gameScene = puzzleLayer.gameScene;
        this.quatGame = puzzleLayer.quatGame;
        this.fontSize = fontSize;
        this.gameBounds = gameBounds;

        return true;
    },

    viewTheme: function(themeName) {
        var theme = this.quatGame.getTheme(themeName);
        theme.name = themeName;

        this.gameScene.applyTheme(theme);
        this.gameScene.applyTheme(theme);
        this.puzzleLayer.solutionLayer.goalWord.changeWord(theme.name);

        var user = this.quatGame.getUser(),
            enabled = user.getTheme() == themeName;

        this.selectedButton.setVisible(user.getPoints() >= theme.unlock);

        this.selectedButton.selected(enabled);
        this.selectedButton.enabled(!enabled);

        if (enabled) {
            this.selectedButton.setText("SELECTED");
        } else {
            this.selectedButton.setText("SELECT");
        }

        this._current = themeName;
    },

    onEnter: function() {
        this._super();

        var quatGame = this.quatGame;

        // Create a list of theme names
        this._themes = Object.keys(quatGame.getThemes());
        var themes = this._themes,
            current = themes.indexOf(quatGame.getUser().getTheme()),
            deltaTheme = function(delta) {
                var newIndex = current + delta;
                newIndex %= themes.length;
                if (newIndex < 0) {
                    newIndex += themes.length;
                }
                current = newIndex;
                return themes[newIndex];
            },
            nextTheme = function(self, delta) {return function() {
                self.viewTheme(delta(1));
            };}(this, deltaTheme),
            prevTheme = function(self, delta) {return function() {
                self.viewTheme(delta(-1));
            };}(this, deltaTheme);

        var fontSize = this.fontSize,
            gameBounds = this.gameBounds;

        var buttonHeight = fontSize * 1.3,
            buttonWidth = gameBounds.width / 2;

        var prevButton = new quat.menu.Button("PREV", this.fontSize, buttonWidth, buttonHeight, prevTheme);
        prevButton.x = gameBounds.x;
        prevButton.y = gameBounds.height - buttonHeight;
        this.addChild(prevButton);
        this.prevButton = prevButton;

        var nextButton = new quat.menu.Button("NEXT", this.fontSize, buttonWidth, buttonHeight, nextTheme);
        nextButton.x = gameBounds.x + buttonWidth;
        nextButton.y = gameBounds.height - buttonHeight;
        this.addChild(nextButton);
        this.nextButton = nextButton;

        var selectCallback = function(self) {return function() {
            self.quatGame.getUser().setTheme(self._current);
            self.selectedButton.setText("SELECTED");
            self.selectedButton.selected(true);
            self.selectedButton.enabled(false);
            self.quatGame.saveToLocal();
        }}(this);
        var selectedButton = new quat.menu.Button("SELECT", this.fontSize, gameBounds.width, buttonHeight, selectCallback);
        selectedButton.x = gameBounds.x;
        selectedButton.y = gameBounds.height - (buttonHeight*2);
        this.addChild(selectedButton);
        this.selectedButton = selectedButton;

        
    },

    setVisible: function(visible) {
        this._super(visible);
        this.nextButton.setVisible(visible);
        this.prevButton.setVisible(visible);
        this.selectedButton.setVisible(visible);

        if (visible) {
            this.viewTheme(this.quatGame.getUser().getTheme());
        }
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