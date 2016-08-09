#include "GameScene.h"

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

void GameScene::generateBounds() {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    gameBounds = new cocos2d::Rect(0, 0, visibleSize.width, visibleSize.height);
}

void GameScene::menuCallback() {
    this->onMenu = !this->onMenu;
    this->puzzleLayer->setVisible(!this->onMenu);
    this->menuLayer->setVisible(this->onMenu);
}

bool GameScene::init()
{
    // Init the super class
    if ( !Layer::init() )
    {
        return false;
    }

    // Generate the bounds of the game space
    generateBounds();

    this->onMenu = false;

    float width    = gameBounds->size.width,
          height   = gameBounds->size.height,
          fontSize = width * Q_FONT_SIZE;

    // Create the background
    background = BackgroundLayer::create();
    addChild(background, 0);

    // Create the puzzle layer
    this->puzzleLayer = PuzzleLayer::create(gameBounds, fontSize);
    addChild(this->puzzleLayer, 1);

    this->menuLayer = MenuLayer::create(gameBounds, fontSize);
    this->menuLayer->setVisible(false);
    addChild(this->menuLayer, 1);

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