#include "User.h"

#include <cmath>
#include <algorithm>

namespace QUAT {

using namespace cocos2d;

User::User() {
	this->subRank = 8192 + 63;
}

int User::getRank() {
	return (this->subRank - (this->subRank % 64)) / 64;
}

int User::getSubRank() {
	return this->subRank;
}

int User::getPuzzlesPlayed() {
	return this->puzzlesPlayed;
}

long int User::getTimePlayed() {
	return this->timePlayed;
}

void User::loadFromBytes(char * bytes) {
	
}

bool User::registerPuzzle(Puzzle * puzzle) {
	// Gets the steps the user took to the solution
	std::vector<std::string> * steps = puzzle->getSteps();

	//// Calculates a heuristic for how hard the puzzle was to the user
	
	// the difference between the number of steps and the par
	int difference = steps->size() - puzzle->getPar();

	// An exponential relationship that reduces the user's rating
	// if they don't play very well, or increases it if they do
	float parDifferenceRating = (pow(0.7, difference) * 255.0) - 127.0;

	// Converts that value to an integer
	int change = (int) floor((parDifferenceRating / 128) * 10);

	this->subRank = std::max(this->subRank + change, 0);

	// Add in the time the user played this puzzle
	this->timePlayed += puzzle->getTime();

	// Increase the number of puzzles played
	this->puzzlesPlayed++;

	log("SOP: %d dRank: %d Rank: %d Subrank: %d", difference, change, this->getRank(), this->subRank);
	
	return difference == 0;
}

void User::toBytes(char * bytes) {
	// cocos2d::FileUtils::getInstance()->getWritablePath()
}

}