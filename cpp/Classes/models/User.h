#ifndef __USER_H__
#define __USER_H__

#include <vector>
#include <string>
#include <cmath>

#include "Dictionary.h"
#include "Puzzle.h"
#include "GameState.h"
#include "TimedState.h"
#include "Blitzer.h"
#include "QuatStream.h"
#include "cocos2d.h"

namespace QUAT {

using namespace std;

class User
{
private:
	int puzzlesPlayed;    // The number of puzzles the user has completed

	bool isPaid,  		    // Whether or not the user has paid to remove ads
       showAd;	        // Whether the UI should show the user an ad

	unsigned long timePlayed,  // The total time (in milliseconds) the user has played
			          lastShownAd; // The timePlayed value in seconds at which the user
			                       // last saw an ad
  
  // Whether or not the user is playing endless
  bool playingEndless;
  
  // Stores the state for both game modes
  GameState * endlessState;
  TimedState * timedState;
  
  // Dictionary that holds valid words
  Dictionary * dictionary;

public:
	User();

  // Returns the current game state for the mode the user
  // is playing.
  GameState * getGameState();

  // Get pointers to the individual states. 
  GameState * getEndlessState();
  GameState * getTimedState();

	/**
	 * Get the number of puzzles the user has completed.
	 */
	int getPuzzlesPlayed();

	/**
	 * Returns the result of adding the puzzle to the current game state.
   *
   * Also increments puzzlesPlayed for bookkeeping.
	 */
	bool registerPuzzle(Puzzle * puzzle);

	/**
	 * Gets the user's total time played in ms.
	 */
	unsigned long getTimePlayed();

  bool isPlayingEndless();

  void setPlayingEndless(bool enabled);

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
