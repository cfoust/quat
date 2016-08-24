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
	int subRank,		  // The user's sub-rank between 0 and 16834
		puzzlesPlayed;    // The number of puzzles the user has completed

	bool isPaid,  		  // Whether or not the user has paid to remove ads
	     showAd;	      // Whether the UI should show the user an ad

	long int timePlayed,  // The total time (in seconds) the user has played 
			 lastShownAd; // The timePlayed value in seconds at which the user
			              // last saw an ad
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
	 * @brief      Whether the UI should show the user an ad.
	 *
	 */
	bool shouldShowAd();

	/**
	 * Exports the user's info to bytes. 
	 * @param bytes Location in memory to put the user's bytes.
	 */
	void toBytes(char * bytes);
};

}

#endif // __USER_H__