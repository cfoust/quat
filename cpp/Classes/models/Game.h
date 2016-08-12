#ifndef __GAME_H__
#define __GAME_H__


#include "Puzzle.h"
#include "Dictionary.h"
#include "PuzzleManager.h"
#include "User.h"

namespace QUAT {

class Game
{
private:
	Puzzle * puzzle;
	PuzzleManager * puzzleManager;
	User * user;
	Dictionary * dictionary;

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

	Dictionary * getDictionary();

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