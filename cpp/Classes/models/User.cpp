#include "User.h"

#include <cmath>
#include <algorithm>

namespace QUAT {

using namespace cocos2d;

User::User() {
	this->subRank = 0;
	this->puzzlesPlayed = 0;
	this->timePlayed = 0;
	this->lastShownAd = 0;
	this->showAd = false;
  this->isPaid = true;
}

int User::displayToSubRank(int displayRank) {
  return this->realToSubRank(this->displayToRealRank(displayRank));
}
int User::displayToRealRank(int displayRank) {
  return 22 * (displayRank - 1);
}

int User::realToSubRank(int realRank) {
  return 64 * realRank;
}
int User::getDisplayRank() {
	int rank = this->getRealRank();
	return ((rank - (rank % 22)) / 22) + 1;
}

int User::getRealRank() {
	return ((this->subRank - (this->subRank % 64)) / 64);
}

int User::getSubRank() {
	return this->subRank;
}

float User::getRankProgress() {
  int currentRank = this->getDisplayRank(),
      lowerBound = this->displayToSubRank(currentRank),
      upperBound = this->displayToSubRank(currentRank + 1);

  return (float) (this->subRank - lowerBound) /
         (float) (upperBound - lowerBound); 
}
int User::getPuzzlesPlayed() {
	return this->puzzlesPlayed;
}

long int User::getTimePlayed() {
	return this->timePlayed;
}


bool User::registerPuzzle(Puzzle * puzzle) {
	// Gets the steps the user took to the solution
	std::vector<std::string> * steps = puzzle->getSteps();

	//// Calculates a heuristic for how hard the puzzle was to the user
	
	// the difference between the number of steps and the par
	int difference = steps->size() - puzzle->getPar();

  // Set difference to be pretty high if the puzzle was skipped
  if (puzzle->skipped) difference = 10;

	// An exponential relationship that reduces the user's rating
	// if they don't play very well, or increases it if they do
	float parDifferenceRating = (pow(0.7, difference) * 255.0) - 127.0;

	// Converts that value to an integer
	int change = (int) floor((parDifferenceRating / 128) * 10);

	this->subRank = std::max(this->subRank + change, 0);

	// Add in the time the user played this puzzle
	this->timePlayed += puzzle->getTime();

	// Show an ad every 5 minutes
	if (((this->timePlayed - this->lastShownAd) > 300000) && !this->isPaid) {
		this->showAd = true;
	}

	// Increase the number of puzzles played
	this->puzzlesPlayed++;

	log("SOP: %d dRank: %d Rank: %d Subrank: %d", difference, change, this->getRealRank(), this->subRank);
	
	return difference == 0;
}

bool User::shouldShowAd() {
	if (this->showAd) {
		this->showAd = false;
		this->lastShownAd = this->timePlayed;
		return true;
	}
	else {
		return false;
	}
}

QuatStream& operator<<(QuatStream& qs, const User& pzl) {
  return qs;
}
QuatStream& operator>>(QuatStream& qs, User& pzl) {
  return qs;
}

}
