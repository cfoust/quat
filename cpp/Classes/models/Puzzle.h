#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include <vector>
#include <string>

#include "Dictionary.h"
#include "QuatStream.h"

namespace QUAT {

using namespace std;
class Puzzle
{
private:
	std::vector<std::string> * steps;
	std::string start, finish;

	int par,   // The ideal number of steps to finish the puzzle
		undos, // The number of times the user hit undo
		rank; // The rank of the puzzle
	
	long int _startTime, // When we last started recording time
			 totalMs;    // The number of milliseconds the user spent on this Puzzle

	// Whether or not we're recording time
	bool timeStarted;

	Dictionary * dictionary;

	// Gets the current time in ms
	long int epochMs();

	/**
	 * Clears any stored data about this puzzle and reverts to an empty puzzle.
	 */
	void clear(); 

public:
	/**
	 * Standard constructor that initializes steps.
	 */
	Puzzle(Dictionary * d);

	/**
	 * Add a word to the solution. Checks to see if it is a valid move. Returns
	 * true if the word was added successfully and false if it was not.
	 * @param word Four-letter string word to add to solution.
	 * @return True if the word was added, false if it is not a word.
	 */
	bool addWord(std::string * word);

	/**
	 * Checks whether the puzzle is solved.
	 * @return Whether the puzzle is solved.
	 */
	bool atGoal();

  /**
   * Whether or not this puzzle was skipped.
   * Adjusts some stuff in the heuristics for rank.
   **/
  bool skipped;
	/**
	 * Gets the last step in the puzzle solution (the current end word.)
	 * @return The last step in the puzzle solution.
	 */
	std::string * getCurrent();

	/**
	 * Gets the first step in the puzzle solution (the start word.)
	 * @return The first step in the puzzle solution.
	 */
	std::string * getFirst();

	/**
	 * Gets the goal word.
	 * @return The goal word.
	 */
	std::string * getGoal();

	/**
	 * Gets the steps vector.
	 */
	std::vector<std::string> * getSteps();

	/**
	 * Gets the par for this puzzle.
	 */
	int getPar();

	/**
	 * Gets the puzzle's rank (0-256).
	 */
	int getRank();

	/**
	 * Gets the number of steps so far.
	 * @return [description]
	 */
	int getStepCount();

	/**
	 * Get the number of milliseconds the user has spent in solving this puzzle.
	 */
	long int getTime();

	/**
	 * Gets whether we're recording time or not.
	 */
	bool getTimeStarted();

	/**
	 * Delete the most recent step in the solution.
	 */
	void goBack();

	/**
	 * Resets this instance to this puzzle.
	 * @param first Pointer to first word.
	 * @param last  Pointer to second word.
	 * @param par   Number of steps to par.
	 */
	void set(std::string * first, std::string * last, int par, int rank);

	/**
	 * Starts (or continues) time recording for this puzzle.
	 */
	void startTime();

	/**
	 * Stops recording time for this puzzle.
	 */
	void stopTime();

	/**
	 * Writes the puzzle (and its progress) to a place in memory.
	 * @param bytes Address of the place to write in memory.
	 */
	void toBytes(char * bytes);

  friend QuatStream& operator<<(QuatStream& qs, const Puzzle& pzl);
  friend QuatStream& operator>>(QuatStream& qs, Puzzle& pzl);
};

}

#endif // __PUZZLE_H__
