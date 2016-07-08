#include "Puzzle.h"
#include "cocos2d.h"

#include <chrono>

namespace QUAT {

// Gets the current time in ms
long int Puzzle::epochMs() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Puzzle::clear() {
	this->steps->clear();
	this->par = 0;
	this->undos = 0;
	this->start = "";
	this->finish = "";
	this->totalMs = 0;
	this->timeStarted = false;
	this->_startTime = 0;
}

Puzzle::Puzzle() {
	this->steps = new std::vector<std::string>();

	// Kind of superfluous, but this can't hurt 
	this->clear();
}

bool Puzzle::addWord(std::string * word) {
	if (word->length() != 4) {
		return false;
	}

	// Ensure the word is in the dictionary
	// if (!wordInDictionary) {
	// 	return false;
	// }
	
	// Can't play the same word twice
	if ((*word) == this->getCurrent()) {
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
	return this->getGoal() == this->getCurrent();
}

void Puzzle::fromBytes(char * bytes) {
	// Reset the instance data
	this->clear();


}

std::string Puzzle::getCurrent() {
	return (*this->steps)[this->steps->size() - 1];
}

std::string Puzzle::getFirst() {
	return this->start;
}

std::string Puzzle::getGoal() {
	return this->finish;
}

int Puzzle::getPar() {
	return this->par;
}

long int Puzzle::getTime() {
	return this->totalMs;
}

void Puzzle::goBack() {
	if (this->steps->size() > 1) {
		this->steps->pop_back();
	}
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


}