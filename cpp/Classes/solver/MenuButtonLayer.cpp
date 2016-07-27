#include "MenuButtonLayer.h"

namespace QUAT {
void MenuButtonLayer::up() {
	cocos2d::log("test");
}

void MenuButtonLayer::entered() {
}
void MenuButtonLayer::left() {
}
bool MenuButtonLayer::init() {
	// Init the super class
    if ( !Clickable::init() )
    {
        return false;
    }

    // Initialize the background
    this->background = cocos2d::Sprite::create("banner.png");

    this->enterCallback = CC_CALLBACK_0(MenuButtonLayer::entered, this);
    this->leaveCallback = CC_CALLBACK_0(MenuButtonLayer::left, this);

    // Rescale it to the proper size
    float height = this->_height,
    	  width = height * 0.52,
    	  scale = height / this->background->getBoundingBox().size.height;

    this->background->setScale(scale, scale);
    this->background->setPositionX(width / 2);
    this->background->setPositionY(height / 2);
    this->addChild(this->background, 1);

    this->textLabel = cocos2d::Label::createWithTTF("20", "fonts/Arimo-Regular.ttf", height * 0.3);
    this->textLabel->setPositionX(width / 2);
    this->textLabel->setPositionY(height * 0.58);
    this->addChild(this->textLabel, 2);

    // Set up the bounds
    this->setHeight(this->_size);
    this->setWidth(this->_size);

	return true;
}


MenuButtonLayer::MenuButtonLayer(float size) {
	this->_size = size;
}

MenuButtonLayer * MenuButtonLayer::create(float size)
{
    MenuButtonLayer *pRet = new(std::nothrow) MenuButtonLayer(size);
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