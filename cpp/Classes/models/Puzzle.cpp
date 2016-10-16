#include "Puzzle.h"
#include "cocos2d.h"

#include <ctype.h>
#include <chrono>

namespace QUAT {

using namespace cocos2d;

// Gets the current time in ms
long int Puzzle::epochMs() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Puzzle::clear() {
	this->steps->clear();
	this->par = 0;
	this->rank = 0;
	this->undos = 0;
	this->start = std::string("AAAA");
	this->finish = std::string("AAAA");
	this->totalMs = 0;
	this->timeStarted = false;
	this->_startTime = 0;
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

	// Check if we're at the goal
	if (this->atGoal()) {
		this->stopTime();
	}

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

long int Puzzle::getTime() {
	return this->totalMs;
}

bool Puzzle::getTimeStarted() {
	return this->timeStarted;
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

void Puzzle::startTime() {
	this->timeStarted = true;
	this->_startTime = this->epochMs();
}

void Puzzle::stopTime() {
	if (!this->timeStarted) {
		return;
	}

	long int difference = this->epochMs() - this->_startTime;

	this->timeStarted = false;
	this->totalMs += difference;
}

void Puzzle::toBytes(char * bytes) {
	// todo: implement
}


}
