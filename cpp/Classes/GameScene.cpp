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

void GameScene::to_GAME() {
    this->menuLayer->setVisible(false);
    this->definitionLayer->setVisible(false);
    this->adLayer->setVisible(false);
    this->puzzleLayer->setVisible(true);
}

void GameScene::to_INFO() {
    this->puzzleLayer->setVisible(false);
    this->definitionLayer->setVisible(false);
    this->adLayer->setVisible(false);
    this->menuLayer->setVisible(true);
}

void GameScene::to_AD() {
    this->puzzleLayer->setVisible(false);
    this->definitionLayer->setVisible(false);
    this->menuLayer->setVisible(false);
    this->adLayer->setVisible(true);
    this->adLayer->startTimer();
}

void GameScene::to_GAME_DEFS() {
    this->menuLayer->setVisible(false);
    this->puzzleLayer->setVisible(false);
    this->adLayer->setVisible(false);
    this->definitionLayer->setVisible(true);
}

void GameScene::to_WB_DEFS() {

}

void GameScene::generateBounds() {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    gameBounds = new cocos2d::Rect(0, 0, visibleSize.width, visibleSize.height);
}

void GameScene::menuCallback() {
    if (this->GSC->state() == GameStateController::GAME) {
        this->GSC->to_INFO();
    }
    else if (this->GSC->state() == GameStateController::INFO) {
        this->GSC->to_GAME();
    }
    else if (this->GSC->state() == GameStateController::GAME_DEFS) {
        this->GSC->to_GAME();
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

    this->GSC = new GameStateController(this);

    // Generate the bounds of the game space
    generateBounds();

    float width    = gameBounds->size.width,
          height   = gameBounds->size.height,
          fontSize = width * Q_FONT_SIZE;

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

    this->adLayer = AdLayer::create(gameBounds, fontSize);
    this->adLayer->setVisible(false);
    addChild(this->adLayer, 1);

    this->definitionLayer = DefinitionLayer::create(gameBounds, 
                                                    fontSize, 
                                                    this->game);
    this->definitionLayer->setVisible(false);
    this->addChild(this->definitionLayer, 1);

    float menuButtonSize   = width * Q_MENUBTN_SIZE,
          menuButtonOffset = width * Q_MENUBTN_OFFSET;
    this->menuButton = MenuButtonLayer::create(menuButtonSize);
    this->menuButton->setPositionX(menuButtonOffset);
    this->menuButton->setPositionY(height - menuButtonOffset);
    this->menuButton->upCallback = CC_CALLBACK_0(GameScene::menuCallback, this);
    this->addChild(this->menuButton);
    
    return true;
}

}