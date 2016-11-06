#include "FutureSightButtonLayer.h"

namespace QUAT {
void FutureSightButtonLayer::up() {
	cocos2d::log("test");
}

void FutureSightButtonLayer::entered() {
}
void FutureSightButtonLayer::left() {
}
bool FutureSightButtonLayer::init() {
	// Init the super class
    if ( !Clickable::init() )
    {
        return false;
    }

    // Initialize the background
    this->background = cocos2d::Sprite::create("future.png");

    this->enterCallback = CC_CALLBACK_0(FutureSightButtonLayer::entered, this);
    this->leaveCallback = CC_CALLBACK_0(FutureSightButtonLayer::left, this);

    // Rescale it to the proper size
    float height = this->_height,
    	  width = height,
    	  scale = height / this->background->getBoundingBox().size.height;

    this->background->setScale(scale,scale);
    this->background->setPositionX(0);
    this->background->setPositionY(0);
    this->background->setOpacity(140);
    this->addChild(this->background, 1);

    // Set up the bounds
    this->setHeight(height);
    this->setWidth(width);

	return true;
}


FutureSightButtonLayer::FutureSightButtonLayer(float height) {
	this->_height = height;
}


FutureSightButtonLayer * FutureSightButtonLayer::create(float height)
{
    FutureSightButtonLayer *pRet = new(std::nothrow) FutureSightButtonLayer(height);
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
