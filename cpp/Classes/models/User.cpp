#include "User.h"

namespace QUAT {

using namespace cocos2d;

int User::getRank() {
	return 0;
}

int User::getSubRank() {
	return 0;
}

int User::getPuzzlesPlayed() {
	return 0;
}

long int User::getTimePlayed() {
	return 0;
}

void User::loadFromBytes(char * bytes) {
	
}

void User::registerPuzzle(Puzzle * puzzle) {
	// Gets the steps the user took to the solution
	std::vector<std::string> * steps = puzzle->getSteps();

	// The difference (in steps) between the number of steps the user took
	// and the puzzle's par.
	int difference = steps->size() - puzzle->getPar();

	log("Difference was %d", difference);

	// Calculate the step difference metric
	float stepDiffMetric;
	if (difference == 0) {
		stepDiffMetric = 256;
	} else {

	}
}

void User::toBytes(char * bytes) {

}

}