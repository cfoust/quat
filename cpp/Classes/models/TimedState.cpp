#include "TimedState.h"

#include <cmath>
#include <chrono>
#include <algorithm>

namespace QUAT {

using namespace cocos2d;

TimedState::TimedState(Dictionary * d) : GameState(d) {
  this->timePlayed = 0;
  this->lastTime = 0;
  this->winRank = 2;
  this->running = false;
  this->done = false;

  for (int i = 0; i < TIMED_RANKS; i++) this->timesComplete[i] = 0;
  for (int i = 0; i < TIMED_RANKS; i++) this->highScore[i] = 0; 
}

void TimedState::setRunning(bool running) {
  this->running = running;
  
  if (!running) {
    this->lastTime = 0;
  }
}

void TimedState::setWinRank(int rank) {
  this->winRank = rank;
}

int TimedState::getWinRank() {
  return this->winRank;
}

void TimedState::reset() {
  this->subRank = 0;
  this->timePlayed = 0;
  this->done = false;
  this->blitzer->clear();
  this->newPuzzle();
}

bool TimedState::isRunning() {
  return this->running;
}

bool TimedState::isDone() {
  return this->done;
}

bool TimedState::canContinue() {
  return (this->subRank > 0) && (this->timePlayed > 0);
}

unsigned long TimedState::getTime() {
  return this->timePlayed;
}

unsigned long TimedState::getHighScore(int rank) {
  return this->highScore[rank];
}

bool TimedState::registerPuzzle(Puzzle * puzzle) {
  bool result = GameState::registerPuzzle(puzzle);
  
  // We're done if the user hit rank 8
  if (this->getDisplayRank() == winRank) {
    this->done = true;
    
    // Stop running
    this->setRunning(false);

    // Manage high score
    if (this->highScore[winRank] >= this->timePlayed) {
      this->highScore[winRank] = this->timePlayed;
    }

    // Add a time completed
    this->timesComplete[winRank]++;
  }

  return result;
}

// The version of the TimedState class's persistent data
#define TIMED_STATE_VERSION 1
void TimedState::serialize(QuatStream & qs) {
  GameState::serialize(qs);

  int version;

  // Check to see whether this is an old version
  bool old = ((version = qs.version(TIMED_STATE_VERSION)) != 0);
  qs.luinteger(&this->timePlayed);

  // Store the high scores and times completed for each rank
  int ranks [3] = {2, 4, 8};
  for (int i = 0; i < 3; i++) {
    qs.luinteger(&this->highScore[ranks[i]]);
    qs.integer(&this->timesComplete[ranks[i]]);
  }

  // Stores the current winRank so it's sticky
  qs.integer(&this->winRank);
}

void TimedState::update(float secs) {
  GameState::update(secs);

  // Increment the timer if we're running
  if (running) {
    // If lastTime is zero, just set it to epochMs
    if (!this->lastTime) {
      this->lastTime = TimeUtils::epochMs();
      return;
    }

    // Calculate the difference since we last called, then reset
    // lastTime
    unsigned long nowEpoch = TimeUtils::epochMs();
    this->timePlayed += nowEpoch - this->lastTime;
    this->lastTime = nowEpoch;
  }
}

}

