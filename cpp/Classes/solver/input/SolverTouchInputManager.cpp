#include "SolverTouchInputManager.h"

#include "../PuzzleLayer.h"
#include "../SolverStateController.h"



namespace QUAT {

using namespace cocos2d;

SolverTouchInputManager::SolverTouchInputManager(SolverStateController * sc, 
							Game * model, 
							PuzzleLayer * puzzleLayer) {
	this->sc = sc;
	this->model = model;
	this->puzzleLayer = puzzleLayer;
}

void SolverTouchInputManager::began(cocos2d::Vec2 * point) {
	if (this->sc->state() == SolverStateController::IDLE) {
		int currentLetter = this->puzzleLayer->pointInCurrentWord(point);

		if (currentLetter != -1) {
			this->lastColumn = currentLetter;
			this->sc->to_CHOOSING_LETTER(currentLetter);
			this->puzzleLayer->updateFromModel();
		}
	}
	else if (this->sc->state() == SolverStateController::CHOOSING_LETTER) {
		int currentLetter = this->puzzleLayer->pointInCurrentWord(point);

		if (currentLetter != -1) {
			this->lastColumn = currentLetter;
			this->sc->to_CHOOSING_LETTER(currentLetter);
			this->puzzleLayer->updateFromModel();
		}
		else if (!this->puzzleLayer->pointInKeyboard(point)) {
			this->sc->to_IDLE();
			this->puzzleLayer->updateFromModel();
		}
		else if (this->puzzleLayer->pointInKeyboardLetter(point)) {
			this->puzzleLayer->changeCurrentLetter(this->lastColumn, this->puzzleLayer->getKeyboardLetter(point));
		}
	}
}

void SolverTouchInputManager::moved(cocos2d::Vec2 * point) {
	if (this->sc->state() == SolverStateController::CHOOSING_LETTER) {
		int currentLetter = this->puzzleLayer->pointInCurrentWord(point);

		if (this->puzzleLayer->pointInKeyboardLetter(point)) {
			this->puzzleLayer->changeCurrentLetter(this->lastColumn, this->puzzleLayer->getKeyboardLetter(point));
		}
		else if ((currentLetter != -1) && (this->lastColumn != currentLetter)) {
			this->lastColumn = currentLetter;
			this->sc->to_CHOOSING_LETTER(currentLetter);
			this->puzzleLayer->updateFromModel();
		}
	}
}

void SolverTouchInputManager::done(cocos2d::Vec2 * point) {
	if (this->sc->state() == SolverStateController::CHOOSING_LETTER) {
		if (this->puzzleLayer->pointInKeyboardLetter(point)) {
			this->puzzleLayer->finishWord();	
		}
	}
}

}