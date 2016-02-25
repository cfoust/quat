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
        GAME: null,
        /*
        When the user is at the main menu.
         */
        MAIN_MENU: null,
        /*
        When the user is choosing a theme.
         */
        LOOK: null
    }
});