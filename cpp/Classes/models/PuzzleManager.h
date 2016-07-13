#ifndef __PUZZLE_MANAGER_H__
#define __PUZZLE_MANAGER_H__

#include <string>
#include <iostream>
#include <fstream>
#include "cocos2d.h"
#include "Puzzle.h"

namespace QUAT {

using namespace std;
class PuzzleManager
{
private:
	struct puzzleRange {
		int startAddress;
		int endAddress;
	};

	Puzzle * puzzle;

	/**
	 * Opens a handle to the puzzles file and returns a pointer to it. Be sure
	 * to close this when done.
	 * @return Pointer to the puzzle file stream.
	 */
	ifstream * openPuzzleFile();

	/**
	 * Gets the start of the header address for an address range of puzzles.
	 * @param  rating Rating 0-255 whose address we want to get.
	 * @return        Address of address range for rating in header block.
	 */
	int getHeaderAddress(int rating);

	/**
	 * Fills a puzzleRange struct in with information from a puzzle file.
	 * @param puzzleFile Pointer to the puzzle file.
	 * @param range      Pointer to the puzzle range to fill.
	 * @param rating     The rating's range to get.
	 */
	void getPuzzleRange(ifstream * puzzleFile, puzzleRange * range, int rating);

	/**
	 * Gets the number of puzzles in this rating.
	 * @param  puzzleFile Pointer to puzzle file.
	 * @param  rating     Rating 0-255 whose number of puzzles we want to get.
	 * @return            Number of puzzles the rating has.
	 */
	int getPuzzleCount(ifstream * puzzleFile, int rating);

	/**
	 * Gets the address of a random puzzle in the given rating.
	 * @param  puzzleFile Pointer to puzzle file.
	 * @param  rating     Rating 0-255 we want to get a puzzle from.
	 * @return            Gets the address of a random puzzle in this rating.
	 */
	int addressOfRandomPuzzle(ifstream * puzzleFile, int rating);

	/**
	 * Parses four bytes of an address into their integer counterparts.
	 * @param  bytes Pointer to four bytes.
	 * @return       Integer representation of those four bytes.
	 */
	int parseAddress(char * bytes);

	/**
	 * Parses the puzzle's par from its header byte pointed to by bytes.
	 * @param  bytes 
	 * @return Integer representing par for this puzzle.  
	 */
	int parsePar(char * bytes);

	/**
	 * Lets you select a sequence of bits from a char bitstring.
	 * @param  byte  Byte to slice up.
	 * @param  start The start index 0-7. The 0-th bit is the furthest to the left.
	 * @param  size  The number of bits to grab.
	 * @return       Unsigned char representing the bits in the given char.
	 */
	char selectFromByte(char byte, int start, int size);

	/**
	 * Parses a sequence of five bytes into the start and finish words specified
	 * by the start and finish params, respectively.
	 * @param bytes  Char array of at least five bytes we can parse into words.
	 * @param start  Pointer to storage for start word.
	 * @param finish Pointer to storage for finish word.
	 */
	void parseWords(char * bytes, std::string * start, std::string * finish);

public:
	PuzzleManager(Puzzle * puzzle);

	/**
	 * Initializes the puzzle manager.
	 */
	void init();

	/**
	 * Gets a puzzle of the indicated rating from the puzzle pool and imports it
	 * into the puzzle instance. 
	 * @param rating 0-255: The rating the puzzle should have. 
	 */
	void fill(int rating);

	/**
	 * Checks how many puzzles there are for a given rating in the puzzle file.
	 * @param  rating 0-255: The rating we should look at.
	 * @return        The number of puzzles there.
	 */
	int getPuzzleCount(int rating);
};

}

#endif // __PUZZLE_MANAGER_H__