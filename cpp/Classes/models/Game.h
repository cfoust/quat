#ifndef __GAME_H__
#define __GAME_H__


#include "cocos2d.h"
#include "Dictionary.h"
#include "Puzzle.h"
#include "GameState.h"
#include "PuzzleManager.h"
#include "QuatStream.h"
#include "User.h"

namespace QUAT {
class Theme;

using namespace std;
class Game
{
private:
	// The puzzle manager, which grabs puzzles from the puzzle file
	PuzzleManager * puzzleManager;

	// The current user
	User * user;

	// The map of strings to themes
	std::map<std::string, Theme *> * themes;

	// Current theme
	Theme * theme;

  std::string getSaveFileName();

public:
	Game();

	/**
	 * Checks whether or not we can load a game state from a local file.
	 */
	bool canLoadFromLocal();

	/**
	 * Returns a pointer to the current user.
	 */
	User * getUser();

  // Some convenience functions for getting these properties of the
  // CURRENT game state. The choice is automatically made based on
  // whether the user is playing Timed Mode or not.
  GameState * getState();
  Puzzle * getPuzzle();
  Blitzer * getBlitzer();

	/**
	 * @brief      Gets a pointer to the dictionary used by the game to 
	 *             check the validity of words and get their definitions.
	 *
	 * @return     The dictionary.
	 */
	Dictionary * getDictionary();

	/**
	 * @brief      Gets the current activated theme.
	 *
	 * @return     The theme.
	 */
	Theme * getTheme();

	/**
	 * @brief      Sends the current game state to the theme so that it can 
	 *             respond to changes.
	 */
	void updateTheme();

	/**
	 * @brief      Sets the theme to the theme given by themeName.
	 *
	 * @param      themeName  The theme name
	 */
	void setTheme(std::string * themeName);

	/**
	 * Load in a game state from a local store of it.
	 */
	void loadFromLocal();


	/**
	 * Dumps the entire current user state to a local file.
	 */
	void saveToLocal();

  // Updates the model based on time delta
  void update(float secs);
};

}

#endif // __GAME_H__
