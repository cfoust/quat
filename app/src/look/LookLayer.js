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
        this.themeName.applyTheme(theme);
        this.leftIcon.applyTheme(theme);
        this.rightIcon.applyTheme(theme);
    },

    viewTheme: function(themeName) {
        var theme = this.quatGame.getTheme(themeName);
        theme.name = themeName;

        this.gameScene.applyTheme(theme);
        this.gameScene.applyTheme(theme);
        this.themeName.changeWord(theme.name);

        var user = this.quatGame.getUser(),
            // Whether or not this is the current theme
            enabled = user.getTheme() == themeName,
            // Whether or not the user has unlocked this theme
            unlocked = user.getPoints() >= theme.unlock,
            // The user's progress in the theme (how many puzzles remain)
            progress = user.getThemeProgressForTheme(themeName),
            // The total number of puzzles the theme has.
            puzzles = theme.puzzles.length;

        // if (!unlocked) {
        //     this.remaining.string = ("You need " + (theme.unlock - user.getPoints()) + " more points to unlock this theme.").toUpperCase();   
        // }

        // this.selectedButton.setVisible(unlocked);
        // this.remaining.setVisible(!unlocked);

        // this.selectedButton.selected(enabled);
        // this.selectedButton.enabled(!enabled);

        // if (enabled) {
        //     this.selectedButton.setText("SELECTED");
        // } else {
        //     this.selectedButton.setText("SELECT");
        // }

        // if (puzzles != 0) {
        //     this.progress.string = progress.toString() + "/" + puzzles.toString() + " PUZZLES SOLVED";
        //     this.progress.setVisible(true);
        // } else {
        //     this.progress.setVisible(false);
        // }


        this._current = themeName;
        this._currentIndex = this._themes.indexOf(themeName);

        // solutionLayer.stepsWord.string = "THEME " + (this._currentIndex + 1).toString() + "/" + this._themes.length.toString();
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
            gap = width * 0.16;

        // Create a word to display the theme name
        var themeName = new quat.solver.WordNode(fontSize, gap);
        themeName.x = gameBounds.x + (width / 2);
        themeName.y = gameBounds.height * 0.6;
        themeName.zIndex = 1;
        themeName.changeWord('TEST');
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
    },

    setOpacity: function(opacity) {
        // Set all children opacity
        var children = this.children;
        for (var i = 0; i < this.childrenCount; i++) {
            var obj = children[i];
            obj.setOpacity(opacity);
        }
    },
});

