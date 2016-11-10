#ifndef __STATES_H__
#define __STATES_H__

namespace QUAT {

/**
 * This file declares all of the possible screen states for the game's
 * user interface. They are only used for the GameScene and
 * GameStateController classes, which just need to pay attention to
 * them for the purpose of controlling which game layer is showing
 * and how to transition between them.
 */

typedef enum {
  // The puzzle solver is the main screen of the game where the user
  // manipulates puzzles to solve them and gain coins.
  S_PuzzleSolver,

  // The main menu displays some basic information about the user's current
  // progress and lets the user navigate the game's other screens.
  S_MainMenu,

  // The game definitions screen is used to show the definitions of the
  // words the user is manipulating on the current game screen.
  S_GameDefinitions,

  // The word book definitions screen shows just the definition for one word.
  // It's used by the word book.
  S_WordbookDefinitions,

  // The ad screen shows an ad to the user that they can close after a few
  // seconds.
  S_Ad
} GAME_STATE;

}

#endif // __STATES_H__
