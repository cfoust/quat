#ifndef __TIMED_STATE_H__
#define __TIMED_STATE_H__

#include <vector>
#include <string>
#include <cmath>

#include "GameState.h"

namespace QUAT {

using namespace std;

class TimedState : public GameState
{
protected:
  // The number of times the user has completed the
  // timed mode
  int timesComplete;
  
  unsigned long timePlayed, // Stores the time played
                highScore;  // The user's high score

  bool running, // Whether the timer is counting upwards
       done;    // Whether we've reached level 8

public:
	TimedState(Dictionary * d);

  // Resets the rank and time to zero
  void reset();

  // Sets whether or not this game state should be recording time
  void setRunning(bool running);

  // Whether or not this game state is recording time
  bool isRunning();

  // Whether or not the user reached rank 8.
  bool isDone();

  // Gets the amount of time that has passed
  // as milliseconds.
  unsigned long getTime();

	/**
	 * Adjusts the user's rank and incorporates statistics from a puzzle.
	 */
	bool registerPuzzle(Puzzle * puzzle);

  // Stores or retrieves data on this object. Used for save files.
  void serialize(QuatStream & qs);

  // Updates the model based on time delta
  void update(float secs);
};

}

#endif // __TIMED_STATE_H__

