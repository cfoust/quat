#include "DefinitionButtonLayer.h"

namespace QUAT {
void DefinitionButtonLayer::up() {
	cocos2d::log("test");
}

void DefinitionButtonLayer::entered() {
}
void DefinitionButtonLayer::left() {
}
bool DefinitionButtonLayer::init() {
	// Init the super class
    if ( !Clickable::init() )
    {
        return false;
    }

    // Initialize the background
    this->background = cocos2d::Sprite::create("definition.png");

    this->enterCallback = CC_CALLBACK_0(DefinitionButtonLayer::entered, this);
    this->leaveCallback = CC_CALLBACK_0(DefinitionButtonLayer::left, this);

    // Rescale it to the proper size
    float height = this->_height,
    	  width = height * 1.15,
    	  scale = height / this->background->getBoundingBox().size.height;

    this->background->setScale(scale,scale);
    this->background->setPositionX(width / 2);
    this->background->setPositionY(height / 2);
    this->addChild(this->background, 1);

    // Set up the bounds
    this->setHeight(height);
    this->setWidth(width);

	return true;
}


DefinitionButtonLayer::DefinitionButtonLayer(float height) {
	this->_height = height;
}


DefinitionButtonLayer * DefinitionButtonLayer::create(float height)
{
    DefinitionButtonLayer *pRet = new(std::nothrow) DefinitionButtonLayer(height);
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