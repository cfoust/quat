#ifndef __TIMED_STATE_H__
#define __TIMED_STATE_H__

#include <vector>
#include <string>
#include <cmath>

#include "GameState.h"
#include "TimeUtils.h"

namespace QUAT {

using namespace std;

#define TIMED_RANKS 12

class TimedState : public GameState
{
protected:
  int winRank;
  
  unsigned long timePlayed, // Stores the time played
                lastTime;   // The last time update() was called
  
  // Stores the high scores for each mode
  unsigned long highScore[TIMED_RANKS];

  // The number of times the user has completed the
  // timed mode
  int timesComplete[TIMED_RANKS];

  bool running, // Whether the timer is counting upwards
       done;    // Whether we've reached the win rank

public:
	TimedState(Dictionary * d);

  // Resets the rank and time to zero
  void reset();

  // Sets whether or not this game state should be recording time
  void setRunning(bool running);

  // Whether or not this game state is recording time
  bool isRunning();

  // Whether or not the user reached rank TIMED_WIN_RANK
  bool isDone();

  // Whether the user can continue a previous state or not
  bool canContinue();

  // Sets the rank the user will win at.
  void setWinRank(int rank);

  // Gets the win rank the user will win at.
  int getWinRank();

  // Gets the amount of time that has passed
  // as milliseconds.
  unsigned long getTime();

  unsigned long getHighScore(int rank);

	/**
	 * Adjusts the user's rank and incorporates statistics from a puzzle.
	 */
	bool registerPuzzle(Puzzle * puzzle) override;

  // Stores or retrieves data on this object. Used for save files.
  void serialize(QuatStream & qs);

  // Updates the model based on time delta
  void update(float secs);
};

}

#endif // __TIMED_STATE_H__

