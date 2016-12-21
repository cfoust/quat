#include "Puzzle.h"
#include "cocos2d.h"

#include <ctype.h>
#include <chrono>

namespace QUAT {

using namespace cocos2d;

bool Puzzle::isStruggling() {
  return (this->totalSec >= 30);
}

void Puzzle::markSkipped() {
  this->skipped = true;
}

bool Puzzle::isSkipped() {
  return this->skipped;
}

#define PUZZLE_VERSION 1
void Puzzle::serialize(QuatStream & qs) {
  int version;
  
  // Check to see whether this is an old version
  bool old = ((version = qs.version(PUZZLE_VERSION)) != 0);

  // The ints
  qs.integer(&this->par);
  qs.integer(&this->undos);
  qs.integer(&this->rank);

  qs.word(&this->start);
  qs.word(&this->finish);

  int steps = this->steps->size();

  // Write the number of steps
  qs.integer(&steps);

  if (qs.isWriting()) {
    // Write out each step
    for (int i = 0; i < steps; i++) {
      std::string word(this->steps->at(i));
      qs.word(&word);
    }
  } else {
    // Clear the vector
    this->steps->clear();

    // Read in each step
    std::string word;
    for (int i = 0; i < steps; i++) {
      qs.word(&word);
      this->steps->push_back(word);      
    }
  }

}

void Puzzle::clear() {
	this->steps->clear();
	this->par = 0;
	this->rank = 0;
	this->undos = 0;
  this->totalSec = 0;
	this->start = std::string("AAAA");
	this->finish = std::string("AAAA");
  this->skipped = false;
}

Puzzle::Puzzle(Dictionary * d) {
	this->steps = new std::vector<std::string>();
	this->dictionary = d;

	// Kind of superfluous, but this can't hurt 
	this->clear();
	this->steps->push_back(std::string("BANE"));
	this->start = std::string("BANE");
	this->finish = std::string("BANK");

}

bool Puzzle::addWord(std::string * word) {

	if (word->length() != 4) {
		return false;
	}

	
	// Then check if it's in the dictionary
	if (this->dictionary->contains(word) == -1) {
		return false;
	}
	
	// Can't play the same word twice
	if ((*word) == (*this->getCurrent())) {
		return false;
	}

	// Push the word
	this->steps->push_back(*word);


	return true;
}

bool Puzzle::atGoal() {
	return (*this->getGoal()) == (*this->getCurrent());
}

std::string * Puzzle::getCurrent() {
	return &(*this->steps)[this->steps->size() - 1];
}

std::string * Puzzle::getFirst() {
	return &this->start;
}

std::string * Puzzle::getGoal() {
	return &this->finish;
}

std::vector<std::string> * Puzzle::getSteps() {
	return this->steps;
}

int Puzzle::getPar() {
	return this->par;
}

int Puzzle::getRank() {
	return this->rank;
}
int Puzzle::getStepCount() {
	return this->steps->size();
}


void Puzzle::goBack() {
	if (this->steps->size() > 1) {
		this->steps->pop_back();
		this->undos++;
	}
}

void Puzzle::set(std::string * first, std::string * last, int par, int rank) {
	this->clear();
	this->start.replace(0,4,*first);
	this->steps->push_back(this->start);
	this->finish.replace(0,4,*last);
	this->par = par;
	this->rank = rank;
}

void Puzzle::update(float secs) {
  this->totalSec += secs;
}

}
