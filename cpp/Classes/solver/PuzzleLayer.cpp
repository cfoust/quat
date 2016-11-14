#include "PuzzleLayer.h"
#include "../Constants.h"
#include "SolverStateController.h"
#include "input/SolverTouchInputManager.h"
#include "../GameStateController.h"
#include "../nodes/RectRadius.h"

#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#include "input/SolverKeyboardManager.h"
#endif

namespace QUAT {


PuzzleLayer * PuzzleLayer::create(cocos2d::Rect * gameBounds, 
                                    BackgroundLayer * background,
                                    float fontSize, 
                                    Game * game,
                                    GameStateController * GSC)
{
    PuzzleLayer *pRet = new(std::nothrow) PuzzleLayer(gameBounds, background, fontSize, game, GSC);
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

    //if (this->keyboardUp) {
        //this->lowerKeyboard();
    //}

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

void PuzzleLayer::onSecond(float dt) {
  auto puzzle = this->game->getPuzzle();
  puzzle->stopTime();
  puzzle->startTime();
  this->buttonsLayer->skipButtonLayer->setVisible(puzzle->isStruggling());
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
    
    // Update the buttons layer
    this->buttonsLayer->updateFromModel(this->game);
    
    // Updates the current word
    this->currentWord->changeWord(puzzle->getCurrent());
    
    this->goalWord->changeWord(puzzle->getGoal());

    // Updates the current word
    this->goalWord->changeWord(puzzle->getGoal());
    
    // Gets the new goal word from the puzzle model
    auto user = this->game->getUser();

    // Update the rank display
    this->bannerButton->update(user->getDisplayRank());

    auto theme = this->game->getTheme();

    // Update the theme with data from the game state
    this->game->getTheme()->update(this->game);

    // Check to see if we have to update the background's colors
    if (theme->getColorSchemeChanged()) {
        this->background->animateScheme(theme->getColorScheme());
    }

    // Transition to the ad screen if we need to
    if (user->shouldShowAd()) {
        this->GSC->setState(S_Ad);
    }

    // Save the game state to a file
    this->game->saveToLocal();
}

std::string * PuzzleLayer::getCurrentWord() {
    return this->currentWord->getWord();
}

void PuzzleLayer::bannerClick() {
}

void PuzzleLayer::skipClick() {
  this->game->newPuzzle();
  this->updateFromModel();
}

void PuzzleLayer::futureSightClick() {
  cocos2d::log("Clicked on futureSight");
}

void PuzzleLayer::undoClick() {
    // Tries to go back one in the solution
    this->game->getPuzzle()->goBack();

    // Updates the GUI from the model
    this->updateFromModel();
}

void PuzzleLayer::definitionClick() {
    this->GSC->setState(S_GameDefinitions);
}

void PuzzleLayer::setEnabled(bool enabled) {
    this->enabled = enabled;
}

void PuzzleLayer::raiseKeyboard() {
    // Set up the steps to move
    auto stepsTextAction = cocos2d::MoveTo::create(Q_KEYBOARD_SLIDE, cocos2d::Vec2(this->buttonsLayer->getPositionX(), this->buttonsFinish));
    this->buttonsLayer->setPositionY(this->buttonsStart);
    
    // Set up the keyboard to move
    auto keyboardAction = cocos2d::MoveTo::create(Q_KEYBOARD_SLIDE, cocos2d::Vec2(this->keyboardLayer->getPositionX(), 0));
    
    // Move the keyboard underground
    this->keyboardLayer->setPositionY(this->keyboardDownPos);

    // Run the animations for both the step indicator and the keyboard
    this->buttonsLayer->runAction(stepsTextAction);
    this->keyboardLayer->runAction(keyboardAction);

    this->keyboardUp = true;
}

bool PuzzleLayer::isKeyboardUp() {
  return this->keyboardUp;
}

void PuzzleLayer::lowerKeyboard() {
    // Set up the steps to move
    auto stepsTextAction = cocos2d::MoveTo::create(Q_KEYBOARD_SLIDE, cocos2d::Vec2(this->buttonsLayer->getPositionX(), this->buttonsStart));
    this->buttonsLayer->setPositionY(this->buttonsFinish);
    
    // Set up the keyboard to move
    auto keyboardAction = cocos2d::MoveTo::create(Q_KEYBOARD_SLIDE, cocos2d::Vec2(this->keyboardLayer->getPositionX(), this->keyboardDownPos));
    this->keyboardLayer->setPositionY(0);
    
    this->buttonsLayer->runAction(stepsTextAction);
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

    this->stepsLayer = StepsLayer::create(fontSize);
    this->stepsLayer->setPositionX(gameBounds->origin.x + (width / 2));
    this->stepsLayer->setPositionY(currentWord->getPositionY() 
                                   + wordSize * Q_WORDS_GAP);
    this->stepsLayer->setVisible(false);
    this->addChild(this->stepsLayer);

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
    this->definitionButton->setVisible(false);
    this->addChild(this->definitionButton);

    this->indicatorLayer = IndicatorLayer::create(this->gameBounds, fontSize);
    this->indicatorLayer->setPositionX(gameBounds->origin.x + (width / 2));
    this->indicatorLayer->setPositionY(currentWord->getPositionY() + height * Q_TEXT_INDICATOR_Y);
    
    this->addChild(this->indicatorLayer);

    // Initializes the keyboard layer, the means by which users can select
    // new letters in the solution
    this->keyboardLayer = QUAT::KeyboardLayer::create(gameBounds, fontSize);
    this->keyboardDownPos = this->keyboardLayer->getHeight() * -1.2;
    this->keyboardLayer->setPositionY(this->keyboardDownPos);
    this->addChild(keyboardLayer);

    // Initialize the keyboard to down
    this->keyboardUp = false;

    // Grab the proper positions for the step counter
    this->buttonsStart = 0;
    this->buttonsFinish = this->keyboardLayer->getHeight();

    // Initialize the buttons layer, which holds all of the buttons we use
    // at the bottom of the screen
    this->buttonsLayer = ButtonsLayer::create(gameBounds, fontSize);
    this->buttonsLayer->setPositionX(gameBounds->origin.x);
    this->buttonsLayer->setPositionY(this->buttonsStart);
    this->addChild(this->buttonsLayer);
    
    // Set up the callbacks for the bottom buttons
    this->buttonsLayer->skipButtonLayer->upCallback = CC_CALLBACK_0(PuzzleLayer::skipClick, this);
    this->buttonsLayer->futureSightButtonLayer->upCallback = CC_CALLBACK_0(PuzzleLayer::futureSightClick, this);

    /*=====  End of Initialization of GUI elements  ======*/

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

    // Register us for second ticks
    this->schedule(schedule_selector(PuzzleLayer::onSecond), 1.0f);
    
    /*=====  End of Input management  ======*/
    

    /*=========================================================
    =            Model Handling and Initialization            =
    =========================================================*/
    

    // Clean up this layer and set it to its default (IDLE) state
    this->goIdle();

    // Updates the view with information from the model
    this->updateFromModel();

    this->background->setScheme(this->game->getTheme()->getColorScheme());
    
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
        this->indicatorLayer->notAWord(*newWord);
    }

    // Checks to see if the puzzle has been completed because of this new word
    if (puzzle->atGoal()) {
        // This returns true if the puzzle was finished with par steps
        result = this->game->getUser()->registerPuzzle(puzzle);

        this->game->newPuzzle();

        this->game->getPuzzle()->startTime();

        if (result) {
          this->indicatorLayer->perfect();
        } else {
          this->indicatorLayer->done();
        }
    }

    this->updateFromModel();
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
void PuzzleLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,
                                   cocos2d::Event* event) {
        this->solverKeyboardManager->input(keyCode, event);
}
#endif


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

PuzzleLayer::PuzzleLayer(cocos2d::Rect * gameBounds, 
                         BackgroundLayer * background,
                         float fontSize, 
                         Game * game,
                         GameStateController * GSC) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
  this->background = background;
  this->game = game;
  this->GSC = GSC;
}

}
