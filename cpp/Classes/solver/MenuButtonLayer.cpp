#include "MenuButtonLayer.h"

namespace QUAT {
void MenuButtonLayer::up() {
	cocos2d::log("Clicked menu button");
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

    this->enterCallback = CC_CALLBACK_0(MenuButtonLayer::entered, this);
    this->leaveCallback = CC_CALLBACK_0(MenuButtonLayer::left, this);
    this->upCallback = CC_CALLBACK_0(MenuButtonLayer::up, this);

    this->circle = RectRadius::create(this->_size, 
                                      this->_size, 
                                      this->_size / 2, 
                                      this->_size * 0.10, 
                                      false);
    this->circle->setColor(cocos2d::Color4B(255,255,255,180));
    this->addChild(this->circle);

    // Set up the bounds
    this->setHeight(this->_size * 2);
    this->setWidth(this->_size * 2);

    this->recalculateBounds();

	return true;
}

void MenuButtonLayer::recalculateBounds() {
    this->bounds->setRect(this->getPositionX() - this->_size, 
                          this->getPositionY() - this->_size, 
                          this->width, 
                          this->height);
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