#include "SkipButtonLayer.h"

namespace QUAT {
void SkipButtonLayer::up() {
	cocos2d::log("test");
}

void SkipButtonLayer::entered() {
}
void SkipButtonLayer::left() {
}
bool SkipButtonLayer::init() {
	// Init the super class
    if ( !Clickable::init() )
    {
        return false;
    }

    // Initialize the background
    this->background = cocos2d::Sprite::create("definition.png");

    this->enterCallback = CC_CALLBACK_0(SkipButtonLayer::entered, this);
    this->leaveCallback = CC_CALLBACK_0(SkipButtonLayer::left, this);

    // Rescale it to the proper size
    float height = this->_height,
    	  width = height,
    	  scale = height / this->background->getBoundingBox().size.height;

    this->background->setScale(scale,scale);
    this->background->setPositionX(0);
    this->background->setPositionY(0);
    this->setOffset(-1 * width / 2, -1 * height / 2);
    this->background->setOpacity(140);
    this->addChild(this->background, 1);

    // Set up the bounds
    this->setHeight(height);
    this->setWidth(width);

	return true;
}


SkipButtonLayer::SkipButtonLayer(float height) {
	this->_height = height;
}


SkipButtonLayer * SkipButtonLayer::create(float height)
{
    SkipButtonLayer *pRet = new(std::nothrow) SkipButtonLayer(height);
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
