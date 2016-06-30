#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include <vector>
#include <string>

namespace QUAT {

class Puzzle
{
private:
	std::vector<std::string> steps;
	std::string start, finish;

public:
	/**
	 * Standard constructor that initializes steps.
	 */
	Puzzle();
	
	/**
	 * Construct a puzzle from an already existing steps vector. Copies to new
	 * vector.
	 */
	Puzzle(std::string * start, std::string * finish);

	/**
	 * Add a word to the solution. Checks to see if it is a valid move. Returns
	 * true if the word was added successfully and false if it was not.
	 * @param word Four-letter string word to add to solution.
	 */
	void addWord(std::string * word);

	/**
	 * Checks whether the puzzle is solved.
	 * @return Whether the puzzle is solved.
	 */
	bool atGoal();

	/**
	 * Creates a Puzzle instance from bytes based on the Puzzle data format.
	 * @param  bytes Array of bytes representing a puzzle.
	 * @return       Puzzle instance representing the puzzle contained by the
	 *               array of bytes.
	 */
	static Puzzle * fromBytes(char * bytes);

	/**
	 * Gets the first step in the puzzle solution (the start word.)
	 * @return The first step in the puzzle solution.
	 */
	std::string getFirst();

	/**
	 * Gets the goal word.
	 * @return The goal word.
	 */
	std::string getGoal();

	/**
	 * Gets the last step in the puzzle solution (the current end word.)
	 * @return The last step in the puzzle solution.
	 */
	std::string getLast();

	/**
	 * Converts an instance of Puzzle into bytes.
	 * @return array of bytes.
	 */
	char * toBytes();

};

}

#endif // __PUZZLE_H__