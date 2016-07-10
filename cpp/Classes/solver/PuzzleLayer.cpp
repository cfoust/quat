#include "PuzzleLayer.h"
#include "SolverStateController.h"
#include "SolverTouchInputManager.h"
#include "../nodes/RectRadius.h"

// USING_NS_CC;

namespace QUAT {


PuzzleLayer * PuzzleLayer::create(cocos2d::Rect * gameBounds, float fontSize)
{
    PuzzleLayer *pRet = new(std::nothrow) PuzzleLayer(gameBounds, fontSize);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void PuzzleLayer::goIdle() {
	if (solverStateController->state() == SolverStateController::CHOOSING_LETTER) {
		this->keyboardLayer->setVisible(false);
	}

	this->solutionLayer->currentWord->unselect();


 //    self.solutionLayer.stepsWord.setVisible(true);
 //    self.puzzleLayer.textIndicatorLayer.setVisible(true);
    this->updateFromModel();
 //    self.solutionLayer.updateFromModel(self.quatGame);
}

void PuzzleLayer::chooseLetter(int column) {
	this->keyboardLayer->setVisible(true);

	auto word = this->solutionLayer->currentWord;    
 //    currentWord.changeWord(self.quatGame.getPuzzle().getCurrentWord());
    word->unselect();
    word->select(column);
}

void PuzzleLayer::changeCurrentLetter(int column, std::string letter) {
    this->solutionLayer->currentWord->changeLetter(column, letter);
}

int PuzzleLayer::pointInCurrentWord(cocos2d::Vec2 * point) {
    return this->solutionLayer->currentWord->pointInWord(point);
}

bool PuzzleLayer::pointInKeyboard(cocos2d::Vec2 * point) {
    return this->keyboardLayer->pointInKeyboard(point);
}

bool PuzzleLayer::pointInKeyboardLetter(cocos2d::Vec2 * point) {
    return this->keyboardLayer->pointInLetter(point);
}

std::string PuzzleLayer::getKeyboardLetter(cocos2d::Vec2 * point) {
    return this->keyboardLayer->getLetter(point);
}

void PuzzleLayer::updateFromModel() {
    auto puzzle = this->game->getPuzzle();

    if (!puzzle->getTimeStarted()) {
        puzzle->startTime();
    }

    this->solutionLayer->currentWord->changeWord(puzzle->getCurrent());
    this->solutionLayer->goalWord->changeWord(puzzle->getGoal());
}

bool PuzzleLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }
    
    solutionLayer = QUAT::SolutionLayer::create(gameBounds, fontSize);
    addChild(solutionLayer, 0);

    keyboardLayer = QUAT::KeyboardLayer::create(gameBounds, fontSize);
    this->addChild(keyboardLayer);

    solverStateController = new SolverStateController(this);

    auto game = new Game();

	
    return true;
}

PuzzleLayer::PuzzleLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}



}