#include "CloseButton.h"


namespace QUAT {

void CloseButton::up() {
    cocos2d::log("Clicked menu button");
}

void CloseButton::entered() {
}
void CloseButton::left() {
}

CloseButton * CloseButton::create(float size) {
	CloseButton *pRet = new(std::nothrow) CloseButton(size);

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

void CloseButton::drawCross() {
	this->node->clear();

    // Draw the line from bottom-left to top-right
    this->node->drawLine(cocos2d::Vec2(-1 * this->size,
                                       -1 * this->size),
                         cocos2d::Vec2(this->size,
                                       this->size),
                         cocos2d::Color4F::WHITE);

    // Draw the line from top-left to bottom-right
    this->node->drawLine(cocos2d::Vec2(-1 * this->size,
                                       this->size),
                         cocos2d::Vec2(this->size,
                                       -1 * this->size),
                         cocos2d::Color4F::WHITE);
}

void CloseButton::recalculateBounds() {
    this->bounds->setRect(this->getPositionX() - this->size, 
                          this->getPositionY() - this->size, 
                          this->width, 
                          this->height);
}
	
bool CloseButton::init() {
	// Init the super class
    if ( !Clickable::init() )
    {
        return false;
    }

    this->enterCallback = CC_CALLBACK_0(CloseButton::entered, this);
    this->leaveCallback = CC_CALLBACK_0(CloseButton::left, this);
    this->upCallback = CC_CALLBACK_0(CloseButton::up, this);

    // Create the node
    this->node = cocos2d::DrawNode::create();
    this->addChild(this->node);

    this->drawCross();

    this->setHeight(this->size * 2);
    this->setWidth(this->size * 2);

    this->recalculateBounds();

    return true;
}

CloseButton::CloseButton(float size) {
	this->size = size / 2;
}

}