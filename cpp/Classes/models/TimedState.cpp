#include "TimedState.h"

#include <cmath>
#include <algorithm>

namespace QUAT {

using namespace cocos2d;

TimedState::TimedState(Dictionary * d) : GameState(d) {
  this->timePlayed = 0;
  this->highScore = 0;
  this->timesComplete = 0;
  this->running = false;
  this->done = false;
}

void TimedState::setRunning(bool running) {
  this->running = running;
}

void TimedState::reset() {
  this->subRank = 0;
  this->timePlayed = 0;
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

unsigned long TimedState::getHighScore() {
  return this->highScore;
}

bool TimedState::registerPuzzle(Puzzle * puzzle) {
  bool result = GameState::registerPuzzle(puzzle);
  
  // We're done if the user hit rank 8
  if (this->getDisplayRank() == TIMED_WIN_RANK) {
    this->done = true;
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
  qs.luinteger(&this->highScore);
  qs.integer(&this->timesComplete);
}

void TimedState::update(float secs) {
  GameState::update(secs);

  // Increment the timer if we're running
  if (running) {
    this->timePlayed += floor(secs * 1000);
  }
}

}

