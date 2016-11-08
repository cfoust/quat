#ifndef __GAME_H__
#define __GAME_H__


#include "Puzzle.h"
#include "Dictionary.h"
#include "PuzzleManager.h"
#include "QuatStream.h"
#include "User.h"

namespace QUAT {
class Theme;

using namespace std;
class Game
{
private:
	// The puzzle the user is working on
	Puzzle * puzzle;

	// The puzzle manager, which grabs puzzles from the puzzle file
	PuzzleManager * puzzleManager;

	// The current user
	User * user;
	
	// The dictionary that holds all of the definitions and valid words
	Dictionary * dictionary;

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
	 * Returns a pointer to the current puzzle.
	 */
	Puzzle * getPuzzle();

	/**
	 * Returns a pointer to the current user.
	 */
	User * getUser();

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
	 * Grabs a new puzzle for the user to play and puts it into the puzzle
	 * instance.
	 */
	void newPuzzle();

	/**
	 * Dumps the entire current user state to a local file.
	 */
	void saveToLocal();
};

}

#endif // __GAME_H__
