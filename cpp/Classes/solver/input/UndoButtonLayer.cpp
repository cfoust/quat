#include "UndoButtonLayer.h"

namespace QUAT {

void UndoButtonLayer::up() {
}

void UndoButtonLayer::entered() {
}

void UndoButtonLayer::left() {
}

bool UndoButtonLayer::init() {
	// Init the super class
    if ( !Clickable::init() )
    {
        return false;
    }

    // Initialize the background
    this->background = cocos2d::Sprite::create(Q_UNDO_SPRITEFILE);

    this->enterCallback = CC_CALLBACK_0(UndoButtonLayer::entered, this);
    this->leaveCallback = CC_CALLBACK_0(UndoButtonLayer::left, this);

    // Rescale it to the proper size
    float scale = this->size / this->background->getBoundingBox().size.height;

    this->background->setScale(scale,scale);
    this->background->setPositionX(this->size / 2);
    this->background->setPositionY(this->size / 2);
    this->addChild(this->background, 1);

    // Set up the bounds
    this->setHeight(this->size);
    this->setWidth(this->size);

	return true;
}


UndoButtonLayer::UndoButtonLayer(float size) {
	this->size = size;
}


UndoButtonLayer * UndoButtonLayer::create(float size)
{
    UndoButtonLayer *pRet = new(std::nothrow) UndoButtonLayer(size);
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


}