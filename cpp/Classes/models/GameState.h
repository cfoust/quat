#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <vector>
#include <string>
#include <cmath>

#include "cocos2d.h"
#include "Puzzle.h"
#include "Blitzer.h"
#include "QuatStream.h"
#include "PuzzleManager.h"

namespace QUAT {

using namespace std;

class GameState
{
protected:
	// The puzzle the user is working on
	Puzzle * puzzle;

  // Manages the puzzles
  PuzzleManager * puzzleManager;

  // Manages all of the multiplier/combo logic
  Blitzer * blitzer;

	int subRank; // The user's sub-rank between 0 and 16834

  // The lower bound (in terms of real rank) for the display rank
  int displayRankStart(int displayRank);

  // Converts a display rank into its corresponding subrank
  int displayToSubRank(int displayRank);

  // Turn a display rank into a real rank.
  int displayToRealRank(int displayRank);

  // Turn a real rank (0-255) into a sub rank (0-16384)
  int realToSubRank(int realRank);

public:
	GameState(Dictionary * d);

  // Method that adjusts the user's subrank.
  // difference is the number of subrank points to change the rank.
  //
  // If we're on a blitz, multiplies the difference by the current multiplier.
  void adjust(int difference);

  // Returns a pointer to the combo/multiplier logic.
  Blitzer * getBlitzer();

  bool isTimed();

  unsigned long getTimePlayed();

	/**
	 * Returns a pointer to the current puzzle.
	 */
	Puzzle * getPuzzle();

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
	 * Grabs a new puzzle for the user to play and puts it into the puzzle
	 * instance.
	 */
	void newPuzzle();

  /**
   * Gets how far the user is in their current rank as
   * a percentage between 0 and 1.
   */
  float getRankProgress();

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

#endif // __GAME_STATE_H__
