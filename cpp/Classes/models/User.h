#ifndef __USER_H__
#define __USER_H__

#include <vector>
#include <string>
#include <cmath>

#include "Puzzle.h"
#include "QuatStream.h"
#include "cocos2d.h"

namespace QUAT {

using namespace std;

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

  // The lower bound (in terms of real rank) for the display rank
  int displayRankStart(int displayRank);

  // Converts a display rank into its corresponding subrank
  int displayToSubRank(int displayRank);

  // Turn a display rank into a real rank.
  int displayToRealRank(int displayRank);

  // Turn a real rank (0-255) into a sub rank (0-16384)
  int realToSubRank(int realRank);
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
   * Gets how far the user is in their current rank as
   * a percentage between 0 and 1.
   */
  float getRankProgress();

	/**
	 * Get the number of puzzles the user has completed.
	 */
	int getPuzzlesPlayed();

	/**
	 * Gets the user's total time played in ms.
	 */
	long int getTimePlayed();

	/**
	 * Adjusts the user's rank and incorporates statistics from a puzzle.
	 */
	bool registerPuzzle(Puzzle * puzzle);

	/**
	 * @brief      Whether the UI should show the user an ad.
	 *
	 */
	bool shouldShowAd();

  void serialize(QuatStream & qs);

  // Updates the model based on time delta
  void update(float secs);
};

}

#endif // __USER_H__
