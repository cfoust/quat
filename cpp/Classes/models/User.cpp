#include "User.h"

#include <cmath>
#include <algorithm>

namespace QUAT {

using namespace cocos2d;

User::User() {
  // Initialize the basic variables
	this->puzzlesPlayed = 0;
	this->timePlayed = 0;
	this->lastShownAd = 0;
	this->showAd = false;
  this->paid = true;
  this->playingEndless = true;
	
  // Load the dictionary
  // We just have one of these because it occupies a fair
  // bit of memory.
	this->dictionary = new Dictionary();
	this->dictionary->loadFromFile();

  // Initialize the game states
  this->endlessState = new GameState(this->dictionary);
  this->timedState = new TimedState(this->dictionary);
}

bool User::isPaid() {
	return this->paid;
}

int User::getPuzzlesPlayed() {
	return this->puzzlesPlayed;
}

GameState * User::getGameState() {
	return playingEndless ? endlessState : timedState;
}

GameState * User::getEndlessState() {
  return endlessState;
}

TimedState * User::getTimedState() {
  return timedState;
}

unsigned long User::getTimePlayed() {
	return this->timePlayed;
}

bool User::isPlayingEndless() {
  return playingEndless;
}

void User::setPlayingEndless(bool enabled) {
  playingEndless = enabled;
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

bool User::registerPuzzle(Puzzle * puzzle) {
  // Increment the puzzles played
  this->puzzlesPlayed++;

  // Return the result of adding the puzzle to the game state
  return this->getGameState()->registerPuzzle(puzzle);
}

// The version of the User class's persistent data
#define USER_VERSION 1
void User::serialize(QuatStream & qs) {
  int version;

  // Check to see whether this is an old version
  bool old = ((version = qs.version(USER_VERSION)) != 0);

  // All of the primitives
  qs.integer(&this->puzzlesPlayed);
  qs.luinteger(&this->timePlayed);
  qs.luinteger(&this->lastShownAd);

  // Serialize the game states
  this->endlessState->serialize(qs);
  this->timedState->serialize(qs);
}

void User::update(float secs) {
  this->timePlayed += floor(secs * 1000);

	// Show an ad every 5 minutes
  // We do this here because it only happens after a puzzle is done
	if (((this->timePlayed - this->lastShownAd) > AD_MS) && !this->paid) {
		this->showAd = true;
	}

  // Update the game states
  this->endlessState->update(secs);
  this->timedState->update(secs);
}

}
