#include "GameScene.h"
#include "BackgroundLayer.h"
#include "solver/PuzzleLayer.h"
#include "menu/MenuButton.h"

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
    log("This is a test");
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

    float fontSize = gameBounds->size.width * 0.10;

    // Create the background
    background = BackgroundLayer::create();
    addChild(background, 0);

    // Create the puzzle layer
    puzzleLayer = PuzzleLayer::create(gameBounds, fontSize);
    addChild(puzzleLayer, 1);
    
    return true;
}

}