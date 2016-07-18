#include "SolverKeyboardManager.h"

#include <string>

#include "PuzzleLayer.h"
#include "SolverStateController.h"

namespace QUAT {

using namespace cocos2d;

SolverKeyboardManager::SolverKeyboardManager(SolverStateController * sc, 
							Game * model, 
							PuzzleLayer * puzzleLayer) {
	this->sc = sc;
	this->model = model;
	this->puzzleLayer = puzzleLayer;
}

void SolverKeyboardManager::input(cocos2d::EventKeyboard::KeyCode keyCode, 
								  cocos2d::Event* event) {
	// Convert the key code to an int
	int code = (int) keyCode;

	// Checks for numbers 1-4, which correspond to selecting that column
	if ((code >= 77) && (code <= 80)) {
		lastColumn = code - 77;
		this->sc->to_CHOOSING_LETTER(lastColumn);
		return;
	}
	// User entered a letter(this->sc->state() == SolverStateController::CHOOSING_LETTER)
	else if ((code >= 124) && 
			 (code <= 149) &&
			 (this->sc->state() == SolverStateController::CHOOSING_LETTER)) {
		// Creates the new letter and attempts to add it to the puzzle
		std::string newLetter = std::string("A");
		newLetter.replace(0,1,1, (char) code - 59);

		this->puzzleLayer->changeCurrentLetter(lastColumn, newLetter);
		this->puzzleLayer->finishWord();
	}
	// The user entered the backspace key
	else if (code == 7) {
		// Go back a step if we're currently idling
		if (this->sc->state() == SolverStateController::IDLE) {
			this->model->getPuzzle()->goBack();
			this->puzzleLayer->updateFromModel();
		}
		// Otherwise just hide the keyboard
		else if (this->sc->state() == SolverStateController::CHOOSING_LETTER) {
			this->sc->to_IDLE();
		}
	}
}
};