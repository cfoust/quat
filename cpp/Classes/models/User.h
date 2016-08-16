#ifndef __USER_H__
#define __USER_H__

#include <vector>
#include <string>

#include "Puzzle.h"
#include "cocos2d.h"

namespace QUAT {

class User
{
private:
	int subRank,
		puzzlesPlayed;

	long int timePlayed;
public:

	User();

	/**
	 * Get the user's rank in terms of 1-12.
	 */
	int getDisplayRank();

	/**
	 * @brief      Gets the user's rank in terms of 0-256.
	 *
	 * @return     The real rank.
	 */
	int getRealRank();

	/**
	 * Gets the user's rank in terms of 0-16384.
	 */
	int getSubRank();

	/**
	 * Get the number of puzzles the user has completed.
	 */
	int getPuzzlesPlayed();

	/**
	 * Gets the user's total time played in ms.
	 */
	long int getTimePlayed();

	/**
	 * Load the user's info from a given set of bytes.
	 */
	void loadFromBytes(char * bytes);

	/**
	 * Adjusts the user's rank and incorporates statistics from a puzzle.
	 */
	bool registerPuzzle(Puzzle * puzzle);

	/**
	 * Exports the user's info to bytes. 
	 * @param bytes Location in memory to put the user's bytes.
	 */
	void toBytes(char * bytes);
};

}

#endif // __USER_H__