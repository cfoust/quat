#include "PuzzleLayer.h"
#include "../Constants.h"
#include "SolverStateController.h"
#include "input/SolverTouchInputManager.h"
#include "../nodes/RectRadius.h"

#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#include "input/SolverKeyboardManager.h"
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
    // Clear any selections on the current word
	this->currentWord->unselect();

    if (this->keyboardUp) {
        this->lowerKeyboard();
    }

    // Make the game interactable
    this->setEnabled(true);
}

void PuzzleLayer::chooseLetter(int column) {
    // Select the proper column
    auto word = this->currentWord;
    word->unselect();
    word->select(column);

    if (!this->keyboardUp) {
        this->raiseKeyboard();
    }

    // Make the game interactable
    this->setEnabled(true);
}

void PuzzleLayer::showDefinitions() {
    // Show the definition dialog
    this->shadeLayer->setVisible(true);
    this->definitionLayer->setVisible(true);

    // Make the rest of the game noninteractable
    this->setEnabled(false);
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

    // We have to adjust the step count in the UI by one
    int stepCount = puzzle->getStepCount() - 1;

    // Shows the undo button only if the user has added more than one word
    this->undo->setVisible(stepCount > 0);
    
    // Same with the steps layer
    this->stepsLayer->setVisible(stepCount > 0);
    
    // Updates the count of steps
    this->stepsLayer->update(stepCount);

    // Shows the over indicator if the user is over par
    this->stepsLayer->setOverPar(puzzle->getStepCount() >= puzzle->getPar());

    // Updates the current word
    this->currentWord->changeWord(puzzle->getCurrent());

    // Gets the new goal word from the puzzle model
    this->goalWord->changeWord(puzzle->getGoal());
    
    // Update the rank display
    this->bannerButton->update(this->game->getUser()->getRank());

}

std::string * PuzzleLayer::getCurrentWord() {
    return this->currentWord->getWord();
}

void PuzzleLayer::bannerClick() {
}

void PuzzleLayer::undoClick() {
    // Tries to go back one in the solution
    this->game->getPuzzle()->goBack();

    // Updates the GUI from the model
    this->updateFromModel();
}

void PuzzleLayer::definitionClick() {
    cocos2d::log("Clicked on definition button");

    // Transition to definitions
    this->solverStateController->to_DEFINITIONS();
}

void PuzzleLayer::setEnabled(bool enabled) {
    this->enabled = enabled;
    this->definitionButton->setEnabled(enabled);
    this->bannerButton->setEnabled(enabled);
}

void PuzzleLayer::raiseKeyboard() {
    // Set up the steps to move
    auto stepsTextAction = cocos2d::MoveTo::create(Q_KEYBOARD_SLIDE, cocos2d::Vec2(this->stepsLayer->getPositionX(), this->stepFinish));
    this->stepsLayer->setPositionY(this->stepStart);
    
    // Set up the keyboard to move
    auto keyboardAction = cocos2d::MoveTo::create(Q_KEYBOARD_SLIDE, cocos2d::Vec2(this->keyboardLayer->getPositionX(), 0));
    
    // Move the keyboard underground
    this->keyboardLayer->setPositionY(-1 * this->keyboardLayer->getHeight());

    // Run the animations for both the step indicator and the keyboard
    this->stepsLayer->runAction(stepsTextAction);
    this->keyboardLayer->runAction(keyboardAction);

    this->keyboardUp = true;
}

void PuzzleLayer::lowerKeyboard() {
    // Set up the steps to move
    auto stepsTextAction = cocos2d::MoveTo::create(Q_KEYBOARD_SLIDE, cocos2d::Vec2(this->stepsLayer->getPositionX(), this->stepStart));
    this->stepsLayer->setPositionY(this->stepFinish);
    
    // Set up the keyboard to move
    auto keyboardAction = cocos2d::MoveTo::create(Q_KEYBOARD_SLIDE, cocos2d::Vec2(this->keyboardLayer->getPositionX(), -1 * this->keyboardLayer->getHeight()));
    this->keyboardLayer->setPositionY(0);
    
    this->stepsLayer->runAction(stepsTextAction);
    this->keyboardLayer->runAction(keyboardAction);
    this->keyboardUp = false;
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
          wordSize = fontSize,
          gap = wordSize * Q_LETTER_GAP;
    
    // Initializes the goal word, which is the word the user is trying to change
    // the start word into.
    this->goalWord = WordNode::create(wordSize, gap);
    goalWord->changeWord(new std::string("GOAL"));
    // Set its position to be horizontally centered
    goalWord->setPosition(gameBounds->origin.x + (width / 2), 
                          height * Q_GOAL_Y);
    this->addChild(goalWord);

    
    // Initializes the current word, which is the word the user is currently
    // operating on
    this->currentWord = BorderedWordNode::create(wordSize, gap);
    currentWord->changeWord(new std::string("WORD"));
    currentWord->setPosition(gameBounds->origin.x + (width / 2), 
                             goalWord->getPositionY() + wordSize * Q_WORDS_GAP);
    // Since this word is interactable, we have to recalculate the bounds
    // in which we track touches
    currentWord->recalculateBounds();
    this->addChild(currentWord);

    // Initialize the banner, which is used to show the rank the user is 
    // currently at
    float bannerHeight = height * Q_BANNER_HEIGHT; 
    this->bannerButton = BannerButtonLayer::create(bannerHeight);

    // The callback called when the user taps on the banner
    this->bannerButton->upCallback = CC_CALLBACK_0(PuzzleLayer::bannerClick, this);
    
    // Sets up the proper positioning of the banner
    this->bannerButton->setPositionX(gameBounds->origin.x + (width * Q_BANNER_X));
    this->bannerButton->setPositionY(height - bannerHeight);
    this->addChild(this->bannerButton);

    // Create and size the undo button
    float undoSize = fontSize * Q_UNDO_SIZE;
    this->undo = UndoButtonLayer::create(undoSize);
    this->undo->upCallback = CC_CALLBACK_0(PuzzleLayer::undoClick, this);
    this->undo->setPositionX(gameBounds->origin.x + width * Q_UNDO_X);
    this->undo->setPositionY(currentWord->getPositionY() - undoSize / 2);
    this->addChild(this->undo);

    // Create and size the definition button
    float defSize = fontSize * Q_DEFINITIONBTN_SIZE;
    this->definitionButton = DefinitionButtonLayer::create(defSize);
    this->definitionButton->upCallback = CC_CALLBACK_0(PuzzleLayer::definitionClick, this);
    this->definitionButton->setPositionX(gameBounds->origin.x + width * Q_DEFINITIONBTN_X);
    this->definitionButton->setPositionY(currentWord->getPositionY() - defSize / 2);
    this->addChild(this->definitionButton);

    this->shadeLayer = BackgroundLayer::create();
    this->shadeLayer->setVisible(false);
    this->addChild(this->shadeLayer, 10);

    this->definitionLayer = DefinitionLayer::create(gameBounds, fontSize);
    this->definitionLayer->setVisible(false);
    this->addChild(this->definitionLayer, 11);

    this->textLayer = TextIndicatorLayer::create(fontSize);
    this->textLayer->setPositionX(gameBounds->origin.x + (width / 2));
    this->textLayer->setPositionY(currentWord->getPositionY() + height * Q_TEXT_INDICATOR_Y);
    
    this->addChild(this->textLayer);

    // Initializes the keyboard layer, the means by which users can select
    // new letters in the solution
    this->keyboardLayer = QUAT::KeyboardLayer::create(gameBounds, fontSize);
    this->keyboardLayer->setPositionY(this->keyboardLayer->getHeight() * -1);
    this->addChild(keyboardLayer);

    // Initialize the keyboard to down
    this->keyboardUp = false;

    // Grab the proper positions for the step counter
    this->stepStart = height * Q_STEPTEXT_DOWN_Y;
    this->stepFinish = this->keyboardLayer->getHeight();

    this->stepsLayer = StepsIndicatorLayer::create(fontSize);
    this->stepsLayer->setPositionX(gameBounds->origin.x + (width / 2));
    this->stepsLayer->setPositionY(this->stepStart);
    this->addChild(this->stepsLayer);

    
    
    /*=====  End of Initialization of GUI elements  ======*/
    
    this->game = new Game();

    /*========================================
    =            Input management            =
    ========================================*/
    
    // Initializes the game's model here (should probably be more global)
    this->solverStateController = new SolverStateController(this);
    this->solverTouchInputManager = new SolverTouchInputManager(this->solverStateController, this->game, this);
    this->enabled = true;
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

    // Attempts to add the word to the solution
    bool result = puzzle->addWord(newWord);

    // If the new word was not a word, tell the user about it
    if (!result) {
        this->textLayer->display((*newWord) + std::string(" is not a word"));
    }

    // Checks to see if the puzzle has been completed because of this new word
    if (puzzle->atGoal()) {
        // This returns true if the puzzle was finished with par steps
        result = this->game->getUser()->registerPuzzle(puzzle);

        this->game->newPuzzle();

        this->game->getPuzzle()->startTime();

        if (result) {
            this->textLayer->display(std::string("Perfect!"));
        } else {
            this->textLayer->display(std::string("Done!"));
        }
    }

    this->updateFromModel();
}

void PuzzleLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, 
                                      cocos2d::Event* event) {
    this->solverKeyboardManager->input(keyCode, event);
}

bool PuzzleLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!this->enabled) {
        return false;
    }

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

    return true;
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