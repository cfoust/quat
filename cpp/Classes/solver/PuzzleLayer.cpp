#include "PuzzleLayer.h"
#include "SolverStateController.h"
#include "SolverTouchInputManager.h"
#include "../nodes/RectRadius.h"

#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#include "SolverKeyboardManager.h"
#endif

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
	this->currentWord->unselect();
}

void PuzzleLayer::chooseLetter(int column) {
	this->keyboardLayer->setVisible(true);

	auto word = this->currentWord;
    word->unselect();
    word->select(column);
}

void PuzzleLayer::changeCurrentLetter(int column, std::string letter) {
    this->currentWord->changeLetter(column, letter);
}

int PuzzleLayer::pointInCurrentWord(cocos2d::Vec2 * point) {
    return this->currentWord->pointInWord(point);
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

    this->undo->setVisible(puzzle->getStepCount() > 1);
    this->currentWord->changeWord(puzzle->getCurrent());
    this->goalWord->changeWord(puzzle->getGoal());
}

std::string * PuzzleLayer::getCurrentWord() {
    return this->currentWord->getWord();
}

void PuzzleLayer::bannerClick() {
    cocos2d::log("Clicked on banner");
}

bool PuzzleLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }

    /*======================================================
    =            Initialization of GUI elements            =
    ======================================================*/

    // Calculates all of the necessary ratios
    float width = gameBounds->size.width,
          height = gameBounds->size.height,
          fourths = width / 4,
          wordSize = fontSize,
          gap = wordSize * 1.8,
          panelHeight = fontSize + (width * .09);
    
    // Initializes the goal word, which is the word the user is trying to change
    // the start word into.
    this->goalWord = WordNode::create(wordSize, gap);
    goalWord->changeWord(new std::string("GOAL"));
    // Set its position to be horizontally centered
    goalWord->setPosition(gameBounds->origin.x + (width / 2), 
                          height * 0.55);
    this->addChild(goalWord);
    
    // Initializes the current word, which is the word the user is currently
    // operating on
    this->currentWord = BorderedWordNode::create(wordSize, gap);
    currentWord->changeWord(new std::string("WORD"));
    currentWord->setPosition(gameBounds->origin.x + (width / 2), 
                             goalWord->getPositionY() + wordSize * 1.6);
    // Since this word is interactable, we have to recalculate the bounds
    // in which we track touches
    currentWord->recalculateBounds();
    this->addChild(currentWord);

    // Initializes the undo button, which allows the user to jump back in the
    // solution
    this->undo = cocos2d::Sprite::create("undo.png");
    undo->setPosition(gameBounds->origin.x + width * 0.07,
                     currentWord->getPositionY());
    // We have to recalculate the scale of the sprite since it's of a fixed
    // size
    float scale = (fontSize * 0.8)/ undo->getBoundingBox().size.height;
    undo->setScale(scale,scale);
    auto box = undo->getBoundingBox();
    this->addChild(undo);

    // Initialize the banner, which is used to show the rank the user is 
    // currently at
    float bannerHeight = height * 0.08; 
    this->bannerButton = BannerButtonLayer::create(bannerHeight);

    // The callback called when the user taps on the banner
    this->bannerButton->upCallback = CC_CALLBACK_0(PuzzleLayer::bannerClick, this);
    
    // Sets up the proper positioning of the banner
    this->bannerButton->setPositionX(gameBounds->origin.x + (width * 0.88));
    this->bannerButton->setPositionY(height - bannerHeight);
    this->addChild(this->bannerButton);

    // Initializes the keyboard layer, the means by which users can select
    // new letters in the solution
    this->keyboardLayer = QUAT::KeyboardLayer::create(gameBounds, fontSize);
    this->addChild(keyboardLayer);
    
    /*=====  End of Initialization of GUI elements  ======*/
    

    /*========================================
    =            Input management            =
    ========================================*/
    
    // Initializes the game's model here (should probably be more global)
    this->solverStateController = new SolverStateController(this);
    this->solverTouchInputManager = new SolverTouchInputManager(this->solverStateController, this->game, this);
    this->trackingTouch = false;

    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    // Means that other touch listeners can grab touches
    touchListener->setSwallowTouches(false);

    // Registers all of our PuzzleLayer-specific touch callbacks
    touchListener->onTouchBegan = CC_CALLBACK_2(PuzzleLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PuzzleLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PuzzleLayer::onTouchEnded, this);

    // Registers the new listener with the global contexts
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    // Enables keyboard input if we are on a desktop platform
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        // Initialize the input manager that handles key presses
        this->solverKeyboardManager = new SolverKeyboardManager(this->solverStateController, this->game, this);

        auto keyboardEventListener = cocos2d::EventListenerKeyboard::create();
        // Register the callback for the event listener
        keyboardEventListener->onKeyPressed = CC_CALLBACK_2(PuzzleLayer::onKeyPressed, this);
        // Add the event listener to the global context
        _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardEventListener, this);
    #endif
    
    /*=====  End of Input management  ======*/
    

    /*=========================================================
    =            Model Handling and Initialization            =
    =========================================================*/
    
    this->game = new Game();

    // Clean up this layer and set it to its default (IDLE) state
    this->goIdle();

    // Updates the view with information from the model
    this->updateFromModel();
    
    /*=====  End of Model Handling and Initialization  ======*/
	
    // Indicates we initialized successfully
    return true;
}

void PuzzleLayer::finishWord() {
    std::string * newWord = this->getCurrentWord();

    this->solverStateController->to_IDLE();

    auto puzzle = this->game->getPuzzle();

    puzzle->addWord(newWord);

    if (puzzle->atGoal()) {
        this->game->getUser()->registerPuzzle(puzzle);


        this->game->newPuzzle();

        // todo: puzzle->startTime()
    }

    this->updateFromModel();
}

void PuzzleLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, 
                                      cocos2d::Event* event) {
    this->solverKeyboardManager->input(keyCode, event);
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