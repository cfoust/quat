#include "Blitzer.h"

#include <cmath>
#include <algorithm>

namespace QUAT {

using namespace cocos2d;


int Blitzer::offset(int current, int delta) {
  int result = (current + delta) % BLITZER_PUZZLE_MAX;

  if (result < 0) result += BLITZER_PUZZLE_MAX;
  
  return result;
}

Blitzer::Blitzer() {
  this->occupied = 0;
  this->comboCount = 0;
  this->changed = false;
  this->blitzing = false;
  this->multiplier = 1;
}

int Blitzer::puzzlesComplete() {
  this->clean();

  return this->occupied;
}

void Blitzer::reset() {
  // Clean the array
  for (int i = 0; i < BLITZER_PUZZLE_MAX; i++) {
    this->finished[i] = 0;
  }

  // Reset the variables
  this->occupied = 0;
  this->index = 0;
}
void Blitzer::clean() {
  int position,
      oldIndex = this->index;
  for (int i = 0; i < this->occupied; i++) {
    position = offset(oldIndex, i);

    // If the puzzle was finished > 30 seconds ago, clear it
    if (this->finished[position] > BLITZER_PUZZLE_SECS) {
      // Move the index up one
      this->index = offset(this->index, 1);
      this->finished[position] = 0;
      this->occupied--;
    } else {
      break;
    }
  }
}

void Blitzer::puzzleComplete() {
  // Clean up the puzzles
  this->clean();
  this->occupied++;

  if (this->blitzing) {
    this->comboCount++;
  }

  if (this->occupied >= BLITZER_PUZZLE_CNT) {
    this->blitzing = true;
    this->remaining = BLITZER_PUZZLE_SECS;

    // Increases the multiplier
    if (this->multiplier < 16) {
      this->multiplier *= 2;
    }

    // Sets up the initial combo count
    if (this->multiplier == 2) {
      this->comboCount = 5;
    }     
    
    cocos2d::log("BLITZ! x%d", this->multiplier);

    // Resets the count
    this->reset();
  }

  cocos2d::log("At x%d! Combo of %d!", this->multiplier, this->comboCount);
}

void Blitzer::update(float secs) {
  for (int i = 0; i < this->occupied; i++) {
    this->finished[(this->index + i) % BLITZER_PUZZLE_MAX] += secs;
  }

  // Make sure we're still in blitz mode
  if (this->blitzing) {
    this->remaining -= secs;
    
    if (this->remaining < 0) {
      this->blitzing = false;
      this->comboCount = 0;
      this->multiplier = 1;
      cocos2d::log("30 seconds passed and lost combo.");
    }
  }
}

}

