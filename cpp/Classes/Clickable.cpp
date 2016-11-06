#include "Clickable.h"

USING_NS_CC;

namespace QUAT {


bool Clickable::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!this->enabled) {
        return false;
    }

    if (this->contains(touch)) {
        this->enterCallback();
    }

    this->tracking = true;

    return true;
}
void Clickable::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!this->tracking) {
        return;
    }

    // If the touch wasn't inside before, but dragged inwards
    if (this->contains(touch) && !this->inside) {
        this->inside = true;
        this->enterCallback();
    }

    if (!this->contains(touch) && this->inside) {
        this->inside = false;
        this->leaveCallback();
    }

}
void Clickable::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    this->tracking = false;

    if (this->contains(touch)) {
        this->leaveCallback();
        this->upCallback();
    }

}

bool Clickable::contains(cocos2d::Touch* touch) {
    auto nodeTouch = this->convertTouchToNodeSpace(touch);
    
    float halfWidth = this->width / 2,
          halfHeight = this->height / 2;

    if (this->debug) cocos2d::log("T(%f,%f)", nodeTouch.x, nodeTouch.y);

    return (((nodeTouch.x < halfWidth) && (nodeTouch.x > (-1 * halfWidth))) &&
           ((nodeTouch.y < halfHeight) && (nodeTouch.y > (-1 * halfHeight))));
}

bool Clickable::init() {
    if ( !Layer::init() )
    {
        return false;
    }

    this->tracking = false;
    this->inside = false;
    this->enabled = true;
    this->debug = false;

    this->width = 0;
    this->height = 0;

    this->xOffset = 0;
    this->yOffset = 0;
    // Initialize the bounds
    this->bounds = new cocos2d::Rect(0,0,0,0);

    // Register for clicks
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    // Means that other touch listeners can grab touches
    touchListener->setSwallowTouches(false);

    touchListener->onTouchBegan = CC_CALLBACK_2(Clickable::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Clickable::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Clickable::onTouchEnded, this);

    // Registers the new listener with the global contexts
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

Clickable::Clickable() {
}

Clickable * Clickable::create() {
    Clickable *pRet = new(std::nothrow) Clickable();
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

void Clickable::setDebug(bool debug) {
    this->debug = debug;
}

void Clickable::setOffset(float x, float y) {
  this->xOffset = x;
  this->yOffset = y;
}
void Clickable::setLeaveCallback(std::function<void(void)> & callback) {
    this->leaveCallback = callback;
}

void Clickable::setEnterCallback(std::function<void(void)> & callback) {
    this->enterCallback = callback;
}

void Clickable::setUpCallback(std::function<void(void)> & callback) {
    this->upCallback = callback;
}

void Clickable::setEnabled(bool enabled) {
    this->enabled = enabled;
}

void Clickable::setWidth(float width) {
    this->width = width;
}

void Clickable::setHeight(float height) {
    this->height = height;
}

void Clickable::setVisible(bool visible) {
    Layer::setVisible(visible);
    this->setEnabled(visible);
}

}
