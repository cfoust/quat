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
            scene.menuLayer.setVisible(false);
            
            scene.puzzleLayer.setThemeChange(false);
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
        },
    },

    init: function(gameScene) {
        this._super();
        this.gameScene = gameScene;
    }
});