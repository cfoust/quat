#ifndef __BLITZER_H__
#define __BLITZER_H__

#include <vector>
#include <string>
#include <math.h>
#include "cocos2d.h"

namespace QUAT {

using namespace std;

#define BLITZER_PUZZLE_MAX 64
#define BLITZER_PUZZLE_SECS 30
#define BLITZER_PUZZLE_CNT 5

class Blitzer
{
private:
  // Stores data on puzzles that have been completed
  // in the past BLITZER_PUZZLE_SECS seconds. This probably will never be
  // exceeded.
  float finished[BLITZER_PUZZLE_MAX];

  float remaining;

  int index,         // The currently occupied index of the finished array
      occupied,      // The number of puzzles occupied in the array
      multiplier,    // The current multiplier
      comboCount;

  bool changed,      // Whether or not the multiplier has changed
       blitzing;

  // Cleans up any puzzles >BLITZER_PUZZLE_SECS seconds
  void clean();

  // Reset all of the puzzle registering info
  // Happens when the user goes up a multiplier
  void reset();

  // Number of puzzles complete in the past X seconds
  int puzzlesComplete();

  // Handles the nasty modulo stuff.
  int offset(int current, int delta);

public:

  // Stops any currently running blitzes
  void clear();

  Blitzer();

  // Marks that a puzzle was just completed
  void puzzleComplete();

  // True when the multiplier has changed since last check.
  bool multiplierChanged();

  // Gets the current integer multiplier
  int getMultiplier();

  // Returns the number of words completed in this combo.
  int numCombo();

  // Whether or not the user is in a blitz.
  bool isBlitzing();

  // The amount of time remaining on this blitz.
  float blitzTimeRemaining();

  float percentRemaining();

  // Updates the model based on time delta
  void update(float secs);
};

}

#endif // __BLITZER_H__
