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
  this->multiplier = 8;
  this->blitzer = new Blitzer();
}

int User::displayRankStart(int displayRank) {
  if (displayRank <= 0) return 0;

  // Recursive algorithm calculates the size of the ranks before this one
  return this->displayRankStart(displayRank - 1) + ((displayRank - 1) * 3);
}

int User::displayToSubRank(int displayRank) {
  return this->realToSubRank(this->displayRankStart(displayRank));
}

int User::displayToRealRank(int displayRank) {
  return this->displayRankStart(displayRank);
}

int User::realToSubRank(int realRank) {
  return 64 * realRank;
}

int User::getDisplayRank() {
	int rank = this->getRealRank();

  // Iterate through the ranks and see which one we fall into
  for (int i = 1; i < 13; i++) {
   if (rank < this->displayRankStart(i)) return i - 1;
  }

  return 12;
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

unsigned long User::getTimePlayed() {
	return this->timePlayed;
}

void User::adjust(int difference) {
  // If the difference is positive, use the multiplier.
  // Otherwise we don't multiply losses.
  if (difference > 0) {
    difference *= this->multiplier;
  }

  this->subRank += difference;

  // Keep us within the bounds of the puzzles
  if (this->subRank < 0) this->subRank = 0;
  if (this->subRank > 16384) this->subRank = 16384;
}

bool User::registerPuzzle(Puzzle * puzzle) {
	// Gets the steps the user took to the solution
	std::vector<std::string> * steps = puzzle->getSteps();

	//// Calculates a heuristic for how hard the puzzle was to the user

	// the difference between the number of steps and the par
	int difference = steps->size() - puzzle->getPar();

  // Set difference to be pretty high if the puzzle was skipped
  if (puzzle->isSkipped()) difference = 10;

	// An exponential relationship that reduces the user's rating
	// if they don't play very well, or increases it if they do
	float parDifferenceRating = (pow(0.7, difference) * 255.0) - 127.0;

	// Converts that value to an integer
	int change = (int) floor((parDifferenceRating / 128) * 10);

  // Adjust the rank
  this->adjust(change);

	// Show an ad every 5 minutes
  // We do this here because it only happens after a puzzle is done
	if (((this->timePlayed - this->lastShownAd) > 300000) && !this->isPaid) {
		this->showAd = true;
	}

	// Increase the number of puzzles played
	this->puzzlesPlayed++;

  this->blitzer->puzzleComplete();

  // Tracks the change in rank and prints it
	//log("SOP: %d dRank: %d Rank: %d Subrank: %d", difference, change, this->getRealRank(), this->subRank);

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


// The version of the User class's persistent data
#define USER_VERSION 1
void User::serialize(QuatStream & qs) {
  int version;

  // Check to see whether this is an old version
  bool old = ((version = qs.version(USER_VERSION)) != 0);

  // All of the primitives
  qs.integer(&this->puzzlesPlayed);
  qs.integer(&this->subRank);
  qs.luinteger(&this->timePlayed);
  qs.luinteger(&this->lastShownAd);
}

void User::update(float secs) {
  this->blitzer->update(secs);
  this->timePlayed += floor(secs * 1000);
}

}
