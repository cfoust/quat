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
    this->game->getPuzzle()->stopTime();
}

void GameScene::enteredForeground() {
    this->game->getPuzzle()->startTime();
}

void GameScene::showLayer(GAME_STATE state) {
    // Show or hide the background shade so other interfaces are clear
    this->background->shadeVisible(state != S_PuzzleSolver);

    // The main menu layer
    this->menuLayer->setVisible(state == S_MainMenu);

    // The layer for displaying game definitions
    this->definitionLayer->setVisible(state == S_GameDefinitions);

    // The layer for ads
    this->adLayer->setVisible(state == S_Ad);

    // The layer that controls the actual game
    this->puzzleLayer->setVisible(state == S_PuzzleSolver);

    this->menuButton->setVisible(state == S_PuzzleSolver);
    this->closeButton->setVisible((state == S_Ad) ||
                                  (state == S_GameDefinitions) ||
                                  (state == S_MainMenu));

}

void GameScene::toState(GAME_STATE state) {
  this->showLayer(state);

  if (state == S_Ad) {
    this->adLayer->startTimer();
  } else if (state == S_MainMenu) {
    this->menuLayer->updateFromModel(this->game);
  }
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

      // Start the timer for the puzzle
      this->game->getPuzzle()->startTime();
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
    this->menuLayer = MenuLayer::create(gameBounds, fontSize);
    this->menuLayer->setVisible(false);
    addChild(this->menuLayer, 1);

    // Initialize the ad layer
    this->adLayer = AdLayer::create(gameBounds, fontSize, this->closeButton);
    this->adLayer->setVisible(false);
    addChild(this->adLayer, 1);

    // Initialize the definition layer
    this->definitionLayer = DefinitionLayer::create(gameBounds,
                                                    fontSize,
                                                    this->game);
    this->definitionLayer->setVisible(false);
    this->addChild(this->definitionLayer, 1);

    // Transition to the main game screen
    this->GSC->setState(S_PuzzleSolver);

    return true;
}

}
