var quat = quat || {};
quat.look = quat.look || {};

quat.look.LookLayer = cc.Layer.extend({
    ctor: function(gameScene, gameBounds, fontSize, gameState) {
        this._super();

        this.gameScene = gameScene;
        this.gameBounds = gameBounds;
        this.fontSize = fontSize;
        this.quatGame = gameState;

        return true;
    },

    applyTheme: function(theme) {
        this.themeName.setColor(theme.colors.text);
        this.lockIcon.setColor(theme.colors.text);
        this.remaining.setColor(theme.colors.text);
        this.puzzlesLeft.setColor(theme.colors.text);
        this.leftIcon.applyTheme(theme);
        this.rightIcon.applyTheme(theme);
        this.selectedButton.applyTheme(theme);
    },

    viewTheme: function(themeName) {
        var theme = this.quatGame.getTheme(themeName);
        theme.name = themeName;

        this.gameScene.applyTheme(theme);
        this.gameScene.applyTheme(theme);
        this.themeName.string = theme.name;

        var user = this.quatGame.getUser(),
            // Whether or not this is the current theme
            enabled = user.getTheme() == themeName,
            // Whether or not the user has unlocked this theme
            unlocked = user.getPoints() >= theme.unlock,
            // The user's progress in the theme (how many puzzles remain)
            progress = user.getThemeProgressForTheme(themeName),
            // The total number of puzzles the theme has.
            puzzles = theme.puzzles.length,
            remaining = puzzles - progress;

        // Stuff that shows up when the theme is unlocked
        this.selectedButton.setVisible(unlocked);
        this.puzzlesLeft.setVisible(unlocked);

        // Stuff that shows up when it isn't
        this.lockIcon.setVisible(!unlocked);
        this.remaining.setVisible(!unlocked);

        // Enabled the select button if the theme is enabled
        this.selectedButton.selected(enabled);
        this.selectedButton.enabled(!enabled);
        this.selectedButton.setText(enabled ? "SELECTED" : "SELECT");

        if (unlocked) {
            this.puzzlesLeft.setVisible(remaining != 0);
            if (remaining != 0) {
                var word = remaining == 1 ? "PUZZLE" : "PUZZLES";
                this.puzzlesLeft.string = remaining.toString() + " " + word + " LEFT";
            }
        } else {
            var points = (theme.unlock - user.getPoints()),
                word = points == 1 ? "point" : "points";
            this.remaining.string = ("You need " + points.toString() + " more " + word + " to unlock this theme.").toUpperCase(); 
        }

        this._current = themeName;
        this._currentIndex = this._themes.indexOf(themeName);
    },

    deltaTheme: function(delta) {
        var newIndex = this._currentIndex + delta,
            themes = this._themes;

        newIndex %= themes.length;
        if (newIndex < 0) {
            newIndex += themes.length;
        }

        this.viewTheme(themes[newIndex]);
    },

    onEnter: function() {
        this._super();

        // Do all of the theme stuff
        var quatGame = this.quatGame;

        // Create a list of theme names
        this._themes = Object.keys(quatGame.getThemes());
        var themes = this._themes,
            current = themes.indexOf(quatGame.getUser().getTheme())
            nextTheme = function(self) {return function() {
                self.deltaTheme(1);
            };}(this),
            prevTheme = function(self) {return function() {
                self.deltaTheme(-1);
            };}(this);

        // Do all of the UI stuff
        var gameBounds = this.gameBounds,
            fontSize = this.fontSize,
            width = gameBounds.width,
            height = gameBounds.height,
            fourths = width / 4,
            gap = width * 0.08;

        // Create a word to display the theme name
        var themeName = new cc.LabelTTF("TEST", "Ubuntu", fontSize, null, cc.TEXT_ALIGNMENT_CENTER);
        themeName.x = gameBounds.x + (width / 2);
        themeName.y = gameBounds.height * 0.6;
        themeName.zIndex = 1;
        this.addChild(themeName);
        this.themeName = themeName;

        // Create the left and right theme buttons
        var leftIcon = new quat.IconButton(fontSize, "\uf0a8", prevTheme);
        leftIcon.x = gameBounds.x;
        leftIcon.y = themeName.y - (fontSize * .55);
        leftIcon.enabled(true);
        this.leftIcon = leftIcon;
        this.addChild(leftIcon);

        var rightIcon = new quat.IconButton(fontSize, "\uf0a9", nextTheme);
        rightIcon.x = gameBounds.x + gameBounds.width - (rightIcon.width);
        rightIcon.y = themeName.y - (fontSize * .55);
        rightIcon.enabled(true);
        this.rightIcon = rightIcon;
        this.addChild(rightIcon);

        // Initialize the parameters for the button size
        var buttonFontSize = fontSize * 0.9,
            buttonHeight = buttonFontSize * 1.3,
            buttonWidth = gameBounds.width * 0.6,
            difference = (gameBounds.width - buttonWidth) / 2;

        // The callback for select
        var selectCallback = function(self) {return function() {
            self.quatGame.setTheme(self._current);
            self.selectedButton.setText("SELECTED");
            self.selectedButton.selected(true);
            self.selectedButton.enabled(false);
            self.quatGame.saveToLocal();
        }}(this);
        var selectedButton = new quat.menu.Button("SELECTED", buttonFontSize, buttonWidth, buttonHeight, selectCallback);
        selectedButton.x = gameBounds.x + difference;
        selectedButton.y = gameBounds.y + (gameBounds.height * 0.16);
        this.addChild(selectedButton);
        this.selectedButton = selectedButton;

        // The size of all the smaller text on this page
        var subsidiarySize = buttonFontSize * 0.5;

        // Lock icon that shows up when a theme is not unlocked.
        var lockIcon = new cc.LabelTTF("\uf023", "Font Awesome", fontSize, null, cc.TEXT_ALIGNMENT_CENTER);
        lockIcon.x = themeName.x;
        lockIcon.y = themeName.y + (fontSize);
        this.addChild(lockIcon);
        this.lockIcon = lockIcon;

        // Create a label to display the theme name
        var puzzlesLeft = new cc.LabelTTF("TEST", "Ubuntu", subsidiarySize, null, cc.TEXT_ALIGNMENT_CENTER);
        puzzlesLeft.x = gameBounds.x + (width / 2);
        puzzlesLeft.y = themeName.y - fontSize;
        puzzlesLeft.boundingWidth = gameBounds.width * 0.7;
        this.addChild(puzzlesLeft);
        this.puzzlesLeft = puzzlesLeft;

        // Create a label to display the theme name
        var remaining = new cc.LabelTTF("TEST", "Ubuntu", subsidiarySize, null, cc.TEXT_ALIGNMENT_CENTER);
        remaining.x = gameBounds.x + (width / 2);
        remaining.y = gameBounds.height * 0.38;
        remaining.boundingWidth = gameBounds.width * 0.7;
        this.addChild(remaining);
        this.remaining = remaining;
    },

    setOpacity: function(opacity) {
        // Set all children opacity
        var children = this.children;
        for (var i = 0; i < this.childrenCount; i++) {
            var obj = children[i];
            obj.setOpacity(opacity);
        }
    },

    setVisible: function(visible) {
        this._super(visible);
        this.leftIcon.enabled(visible);
        this.rightIcon.enabled(visible);
    }
});

