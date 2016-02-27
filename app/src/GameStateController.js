var quat = quat || {};

quat.GameStateController = quat.StateController.extend({
    states: {
        /*
        When only the current solution progress is showing.
         */
        IDLE: null,

        GESTURING: null,
        /*
        The user has started swiping to the right to get to another menu.
         */
        SWIPING_RIGHT: null
    }
});

quat.ScreenStateController = quat.StateController.extend({
    states: {
        /*
        When the user is playing the vanilla game.
         */
        GAME: function(self) {
            var scene = self.gameScene,
                puzzleLayer = scene.puzzleLayer;

            self.currentLayer = puzzleLayer;
            puzzleLayer.setVisible(true);
            puzzleLayer.setThemeChange(false);

            var game = scene.gameState,
                puzzle = game.getPuzzle(),
                indicator = puzzleLayer.textIndicatorLayer;

            indicator.stopAllActions();
            indicator.clearMessages();
            if (puzzle.isSpecial()) {
                puzzleLayer.textIndicatorLayer.addMessage(puzzle.getSpecialText().toUpperCase(), true);
            }
            
            scene.menuLayer.setVisible(false);
        },
        /*
        When the user is at the main menu.
         */
        MAIN_MENU: function(self) {
            var scene = self.gameScene,
                menuLayer = scene.menuLayer;
            menuLayer.setVisible(true);
            self.currentLayer = menuLayer;
            scene.puzzleLayer.setVisible(false);
            scene.applyThemeByName(scene.gameState.getUser().getTheme());
        },
        LOOK: function(self) {
            var scene = self.gameScene,
                puzzleLayer = self.gameScene.puzzleLayer;

            // Set the current layer
            self.currentLayer = puzzleLayer;
            
            // Make the other ones invisible
            scene.menuLayer.setVisible(false);
            puzzleLayer.setVisible(true);
            
            // Set up the puzzleLayer for LOOK changing
            scene.puzzleLayer.setThemeChange(true);
            scene.puzzleLayer.themeChangeLayer.viewTheme(scene.gameState.getUser().getTheme());
        },
        STATS: function(self) {
            var scene = self.gameScene,
                statsLayer = self.gameScene.statsLayer;

            // Set the current layer
            self.currentLayer = statsLayer;

            statsLayer.updateData();
            
            // Make the other ones invisible
            scene.menuLayer.setVisible(false);
            statsLayer.setVisible(true);
            statsLayer.setOpacity(255);
        },
        ABOUT: function(self) {
            var scene = self.gameScene,
                aboutLayer = self.gameScene.aboutLayer;

            // Set the current layer
            self.currentLayer = aboutLayer;
            
            // Make the other ones invisible
            scene.menuLayer.setVisible(false);
            aboutLayer.setVisible(true);
            aboutLayer.setOpacity(255);
        },
    },

    init: function(gameScene) {
        this._super();
        this.gameScene = gameScene;
    }
});