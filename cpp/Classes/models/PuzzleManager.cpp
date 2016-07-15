#include "PuzzleManager.h"

namespace QUAT {

ifstream * PuzzleManager::openPuzzleFile() {
	std::string filename = cocos2d::FileUtils::getInstance()->fullPathForFilename("puzzles.quat");
	std::ifstream * puzzleFile = new std::ifstream(filename, ios::in|ios::binary|ios::ate);
	return puzzleFile;
}

int PuzzleManager::getHeaderAddress(int rating) {
	return rating * 8;
}

void PuzzleManager::getPuzzleRange(ifstream * puzzleFile, 
								   puzzleRange * range, 
								   int rating) {
	int headerAddress = this->getHeaderAddress(rating);

	// Seek to the header for this rating range
	puzzleFile->seekg(headerAddress);

	// Read and parse the first address
	char * firstBytes = new char[4];
	puzzleFile->read(firstBytes, 4);
	range->startAddress = this->parseAddress(firstBytes);

	// Read and parse the second address
	char * secondBytes = new char[4];
	puzzleFile->read(secondBytes, 4);
	range->endAddress = this->parseAddress(secondBytes);
}

int PuzzleManager::getPuzzleCount(ifstream * puzzleFile, int rating) {
	struct puzzleRange range;

	// Fill in the addresses for this puzzle
	this->getPuzzleRange(puzzleFile, &range, rating);

	return (range.endAddress - range.startAddress) / 6;
}

int PuzzleManager::addressOfRandomPuzzle(ifstream * puzzleFile, int rating) {
	struct puzzleRange range;

	this->getPuzzleRange(puzzleFile, &range, rating);

	int count = (range.endAddress - range.startAddress) / 6;

	int randomIndex = cocos2d::RandomHelper::random_int(0, count - 1);

	return range.startAddress + (randomIndex * 6);
}

int PuzzleManager::parsePar(char * bytes) {
	return (int) this->selectFromByte(bytes[0], 4, 4);
}

char PuzzleManager::selectFromByte(char byte, int start, int size) {
	return (((unsigned char) (byte << start)) >> (8 - size));
}

void PuzzleManager::parseWords(char * bytes, std::string * start, std::string * finish) {
	int startByte,          // Byte the letter starts in 
		endByte,            // Byte the letter ends in
		startIndex,         // Index in the first byte the letter starts
		endIndex,           // Index in the last byte (might still be first) the letter ends
		startIndexRelative, // Relative (byte-local) index for start
		size;				// Size that is in the left byte

	char letter; // Stores the letter

	// Parse through all 8 letters
	for (int i = 0; i < 8; i++) {
		// Calculates all of the nifty variables
		startIndex = (i * 5);
		endIndex = ((i + 1) * 5);

		// Calculate the byte index for the start and the end
		startByte = (startIndex - (startIndex % 8)) / 8;
		endByte = (endIndex - (endIndex % 8)) / 8;

		// Calculates the local index for each index
		startIndexRelative = startIndex % 8;

		// The char falls within the same byte
		if (startByte == endByte) {
			// We just grab the byte sequence we need
			letter = this->selectFromByte(bytes[1 + startByte], 
										  startIndexRelative,
										  5);
		}
		// The char falls across two bytes
		else {
			size = 8 - startIndexRelative;
			// We combine the two sequences of bytes
			letter = (this->selectFromByte(bytes[1 + startByte], 
										  startIndexRelative,
										  size) << (5 - size))
					 | // The magic or bar
					 this->selectFromByte(bytes[1 + endByte], 
										  0,
										  5 - size);
		}

		// Adds in the proper offset to get it back to A-Z
		letter += 97;

		letter = toupper(letter);

		// Fill it into the strings
		if (i < 4) {
			start->replace(i, 1, 1, letter);
		} else {
			finish->replace(i - 4, 1, 1, letter);
		}
	}
}

int PuzzleManager::parseAddress(char * bytes) {
	unsigned int address = 0;

	// Add in all of the bytes
	for (int i = 0; i < 4; i++) {
		address = (address << 8) + (unsigned char) bytes[i];
	}

	return address;
}

PuzzleManager::PuzzleManager(Puzzle * puzzle) {
	this->puzzle = puzzle;
}

void PuzzleManager::init() {
	this->fill(0);
}

void PuzzleManager::fill(int rating) {
	ifstream * puzzleFile = this->openPuzzleFile();
	
	// Get a random puzzle's address within this range
	int address = this->addressOfRandomPuzzle(puzzleFile, rating);

	// Seek to the puzzle's location
	puzzleFile->seekg(address);
	
	// Read the puzzle's bytes
	char * puzzleBytes = new char[6];
	puzzleFile->read(puzzleBytes, 6);

	int par = this->parsePar(puzzleBytes);

	// Parse the start and finish words
	std::string * start = new std::string("AAAA"),
			    * finish = new std::string("AAAA");
	this->parseWords(puzzleBytes, start, finish);

	// Sets the puzzle
	this->puzzle->set(start, finish, par, rating);
}

int PuzzleManager::getPuzzleCount(int rating) {
	ifstream * puzzleFile = this->openPuzzleFile();
	int count = this->getPuzzleCount(puzzleFile, rating);
	puzzleFile->close();
	return count;
}

};