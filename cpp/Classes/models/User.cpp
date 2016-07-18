#include "User.h"

#include <cmath>

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

	// Gets the declared rank of the puzzle (0-255)
	int rank = puzzle->getRank();

	log("Calculating puzzle performance heuristics.");

	// ##################################################
	// ################# PAR DIFFERENCE #################
	// ##################################################
	// The difference (in steps) between the number of steps the user took
	// and the puzzle's par. Since 255 is considered the "perfect" rank,
	// getting par is 255 and we fall off logarithmically from there.
	
	int difference = steps->size() - puzzle->getPar();
	float parDifferenceRating = pow(0.5, difference) * 255.0;
	log("parDifferenceRating: %.2f", parDifferenceRating);

	
}

void User::toBytes(char * bytes) {

}

}