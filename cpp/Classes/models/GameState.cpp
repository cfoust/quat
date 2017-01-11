#include "GameState.h"

#include <cmath>
#include <algorithm>

namespace QUAT {

using namespace cocos2d;

GameState::GameState(Dictionary * d) {
  // Initialize all of the variables to their base states
	this->subRank = 0;
  this->blitzer = new Blitzer();

  // Initialize the puzzle for this GameState
  this->puzzle = new Puzzle(d);

  // The puzzle manager reads the puzzle file and fills
  // the puzzle instance with new puzzles
	this->puzzleManager = new PuzzleManager(this->puzzle);
	this->puzzleManager->init();
}

int GameState::displayRankStart(int displayRank) {
  if (displayRank <= 0) return 0;

  // Recursive algorithm calculates the size of the ranks before this one
  return this->displayRankStart(displayRank - 1) + ((displayRank - 1) * 3);
}

void GameState::setRunning(bool running) {
  this->running = running;
}

int GameState::displayToSubRank(int displayRank) {
  return this->realToSubRank(this->displayRankStart(displayRank));
}

int GameState::displayToRealRank(int displayRank) {
  return this->displayRankStart(displayRank);
}

int GameState::realToSubRank(int realRank) {
  return 64 * realRank;
}

int GameState::getDisplayRank() {
	int rank = this->getRealRank();

  // Iterate through the ranks and see which one we fall into
  for (int i = 1; i < 13; i++) {
   if (rank < this->displayRankStart(i)) return i - 1;
  }

  return 12;
}

Blitzer * GameState::getBlitzer() {
	return this->blitzer;
}

Puzzle * GameState::getPuzzle() {
	return this->puzzle;
}

int GameState::getRealRank() {
	return ((this->subRank - (this->subRank % 64)) / 64);
}

int GameState::getSubRank() {
	return this->subRank;
}

float GameState::getRankProgress() {
  int currentRank = this->getDisplayRank(),
      lowerBound = this->displayToSubRank(currentRank),
      upperBound = this->displayToSubRank(currentRank + 1);

  return (float) (this->subRank - lowerBound) /
         (float) (upperBound - lowerBound);
}


void GameState::adjust(int difference) {
  // If the difference is positive, use the multiplier.
  // Otherwise we don't multiply losses.
  if (difference > 0) {
    difference *= this->blitzer->getMultiplier();
  }

  this->subRank += difference;

  // Keep us within the bounds of the puzzles
  if (this->subRank < 0) this->subRank = 0;
  if (this->subRank > 16384) this->subRank = 16384;
}

bool GameState::registerPuzzle(Puzzle * puzzle) {
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

  this->blitzer->puzzleComplete();

  // Tracks the change in rank and prints it
	//log("SOP: %d dRank: %d Rank: %d Subrank: %d", difference, change, this->getRealRank(), this->subRank);

	return difference == 0;
}

void GameState::newPuzzle() {
	this->puzzleManager->fill(this->getRealRank());
}

// The version of the GameState class's persistent data
#define GAME_STATE_VERSION 1
void GameState::serialize(QuatStream & qs) {
  int version;

  // Check to see whether this is an old version
  bool old = ((version = qs.version(GAME_STATE_VERSION)) != 0);

  // All of the primitives
  qs.integer(&this->subRank);
  
  // Serialize the puzzle
  this->puzzle->serialize(qs);
}

void GameState::update(float secs) {
  if (!running) return;

  this->blitzer->update(secs);
}

}

