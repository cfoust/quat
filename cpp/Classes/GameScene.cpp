#include "GameScene.h"
#include "GameStateController.h"

namespace QUAT {

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void GameScene::enteredBackground() {
    this->game->saveToLocal();
}

void GameScene::enteredForeground() {
}

void GameScene::showLayer(GAME_STATE state) {
  // Show or hide the background shade so other interfaces are clear
  this->background->shadeVisible(state == S_MainMenu);

  // The main menu layer
  this->menuLayer->setVisible(state == S_MainMenu);

  // The layer for ads
  this->adLayer->setVisible(state == S_Ad);

  // The layer that controls the actual game
  this->puzzleLayer->setVisible(state == S_PuzzleSolver);

  this->menuButton->setVisible((state == S_PuzzleSolver) ||
                               (state == S_TimedTransition));

  this->timedTransitionLayer->setVisible(state == S_TimedTransition);

  this->closeButton->setVisible((state == S_Ad) ||
                                (state == S_GameDefinitions) ||
                                (state == S_MainMenu));
}

void GameScene::toState(GAME_STATE state) {
  // Start the timer for the ad screen since we're
  // moving to it
  if (state == S_Ad) {
    this->adLayer->startTimer();
  // Update the menu before we change to it
  } else if (state == S_MainMenu) {
    this->menuLayer->updateFromModel(this->game);
  // Same for the puzzle layer
  } else if (state == S_PuzzleSolver) {
    this->puzzleLayer->updateFromModel();
  }

  // Sets the layer to be visible
  this->showLayer(state);
}

void GameScene::generateBounds() {
  Size visibleSize = Director::getInstance()->getVisibleSize();

  gameBounds = new cocos2d::Rect(0, 0, visibleSize.width, visibleSize.height);
}

void GameScene::menuCallback() {
    if (this->GSC->state() == S_PuzzleSolver) {
        this->GSC->setState(S_MainMenu);
    }
    else if ((this->GSC->state() == S_MainMenu) ||
             (this->GSC->state() == S_GameDefinitions)) {
        this->GSC->setState(S_PuzzleSolver);
    }
}

bool GameScene::init()
{
    // Init the super class
    if ( !Layer::init() )
    {
        return false;
    }

    // Initialize the game model
    this->game = new Game();

    // Load our game file if we can
    if (this->game->canLoadFromLocal()) {
      // Load the local game save
      this->game->loadFromLocal();
    }

    this->GSC = new GameStateController(this);

    // Generate the bounds of the game space
    generateBounds();

    float width    = gameBounds->size.width,
          height   = gameBounds->size.height,
          fontSize = width * Q_FONT_SIZE;

    float menuButtonSize   = width * Q_MENUBTN_SIZE,
          menuButtonOffset = width * Q_MENUBTN_OFFSET;
    this->menuButton = MenuButtonLayer::create(menuButtonSize);
    this->menuButton->setPositionX(menuButtonOffset);
    this->menuButton->setPositionY(height - menuButtonOffset);
    this->menuButton->upCallback = CC_CALLBACK_0(GameScene::menuCallback, this);
    this->addChild(this->menuButton, 10);

    this->closeButton = CloseButton::create(menuButtonSize);
    this->closeButton->setPositionX(menuButtonOffset);
    this->closeButton->setPositionY(height - menuButtonOffset);
    this->closeButton->upCallback = CC_CALLBACK_0(GameScene::menuCallback, this);
    this->addChild(this->closeButton, 10);

    // Create the background
    background = BackgroundLayer::create();
    addChild(background, 0);

    // Create the puzzle layer
    this->puzzleLayer = PuzzleLayer::create(gameBounds,
                                            this->background,
                                            fontSize,
                                            this->game,
                                            this->GSC);
    addChild(this->puzzleLayer, 1);

    // Create the menu layer
    this->menuLayer = MenuLayer::create(gameBounds, 
                                        fontSize, 
                                        this->game,
                                        this->GSC);
    this->menuLayer->setVisible(false);
    addChild(this->menuLayer, 1);

    // Create the timed transition layer
    this->timedTransitionLayer = TimedTransitionLayer::create(gameBounds);
    this->timedTransitionLayer->setVisible(false);
    this->addChild(this->timedTransitionLayer, 1);

    // Initialize the ad layer
    this->adLayer = AdLayer::create(gameBounds, fontSize, this->closeButton);
    this->adLayer->setVisible(false);
    addChild(this->adLayer, 1);

    // Transition to the main game screen
    this->GSC->setState(S_PuzzleSolver);

    // Schedule the update loop
    this->scheduleUpdate();

    return true;
}

void GameScene::update(float delta) {
  this->game->update(delta);
}

}
