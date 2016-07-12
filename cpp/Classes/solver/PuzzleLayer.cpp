#include "PuzzleLayer.h"
#include "SolverStateController.h"
#include "SolverTouchInputManager.h"
#include "../nodes/RectRadius.h"


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
	this->keyboardLayer->setVisible(false);
	this->solutionLayer->currentWord->unselect();
}

void PuzzleLayer::chooseLetter(int column) {
	this->keyboardLayer->setVisible(true);

	auto word = this->solutionLayer->currentWord;
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

    this->solutionLayer->undo->setVisible(puzzle->getStepCount() > 1);
    this->solutionLayer->currentWord->changeWord(puzzle->getCurrent());
    this->solutionLayer->goalWord->changeWord(puzzle->getGoal());
}

std::string * PuzzleLayer::getCurrentWord() {
    this->solutionLayer->currentWord->getWord();
}

bool PuzzleLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->solutionLayer = QUAT::SolutionLayer::create(gameBounds, fontSize);
    addChild(solutionLayer, 0);

    this->keyboardLayer = QUAT::KeyboardLayer::create(gameBounds, fontSize);
    this->addChild(keyboardLayer);

    this->solverStateController = new SolverStateController(this);

    this->game = new Game();

    this->solverTouchInputManager = new SolverTouchInputManager(this->solverStateController, this->game, this);

    this->trackingTouch = false;

    //Create a "one by one" touch event listener (processes one touch at a time)
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    touchListener->setSwallowTouches(false);

    touchListener->onTouchBegan = CC_CALLBACK_2(PuzzleLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PuzzleLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PuzzleLayer::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    this->updateFromModel();
	
    return true;
}

bool PuzzleLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!this->isVisible()) {
        return false;
    }

    if (this->trackingTouch) {
        return false;
    } else {
        this->trackingTouch = true;
    }
    cocos2d::Vec2 point = touch->getLocation();

    this->solverTouchInputManager->began(&point);
}
void PuzzleLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    cocos2d::Vec2 point = touch->getLocation();
    this->solverTouchInputManager->moved(&point);
}
void PuzzleLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    cocos2d::Vec2 point = touch->getLocation();
    this->solverTouchInputManager->done(&point);
    this->trackingTouch = false;
}

PuzzleLayer::PuzzleLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}



}