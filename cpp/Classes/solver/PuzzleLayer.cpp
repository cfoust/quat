#include "PuzzleLayer.h"
#include "SolverStateController.h"
#include "../models/Puzzle.h"
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

 //    self.solutionLayer.updateFromModel(self.quatGame);
}

void PuzzleLayer::chooseLetter(int column) {
	this->keyboardLayer->setVisible(true);

	auto word = this->solutionLayer->currentWord;    
 //    currentWord.changeWord(self.quatGame.getPuzzle().getCurrentWord());
    word->unselect();
    word->select(column);
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
	
    return true;
}

PuzzleLayer::PuzzleLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}



}