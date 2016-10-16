#include "Clickable.h"


USING_NS_CC;

namespace QUAT {

void Clickable::recalculateBounds() {
    this->bounds->setRect(this->getPositionX() + this->xOffset, 
                          this->getPositionY() + this->yOffset, 
                          this->width, 
                          this->height);
    if (this->debug) {
        cocos2d::log("Regenerated bounds (D) (%f,%f,%f,%f)", this->bounds->origin.x,
                                                 this->bounds->origin.y,
                                                 this->bounds->size.width,
                                                 this->bounds->size.height);
    }
    
}

bool Clickable::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!this->enabled) {
        return false;
    }

    if (this->contains(touch)) {
        this->enterCallback();
    }

    this->tracking = true;

    if (this->debug) {
        Vec2 loc = touch->getLocation();
        cocos2d::log("B%d: (%f, %f)", this->contains(touch), loc.x, loc.y);
    }

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

    if (this->debug) {
        Vec2 loc = touch->getLocation();
        cocos2d::log("M%d: (%f, %f)", this->contains(touch), loc.x, loc.y);
    }
}
void Clickable::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    this->tracking = false;

    if (this->contains(touch)) {
        this->leaveCallback();
        this->upCallback();

        if (this->debug) {
            cocos2d::log("Click in rect: (%f,%f,%f,%f)", this->bounds->origin.x,
                                                         this->bounds->origin.y,
                                                         this->bounds->size.width,
                                                         this->bounds->size.height);
        }
    }

    if (this->debug) {
        Vec2 loc = touch->getLocation();
        cocos2d::log("E%d: (%f, %f)", this->contains(touch), loc.x, loc.y);
    }
}

bool Clickable::contains(cocos2d::Touch* touch) {
    return this->bounds->containsPoint(touch->getLocation());
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

void Clickable::setPosition(const cocos2d::Vec2 & position) {
    Layer::setPosition(position);
    this->recalculateBounds();
}
void Clickable::setPosition(float x, float y) {
    Layer::setPosition(x, y);
    this->recalculateBounds();
}
void Clickable::setPositionX(float x) {
    Layer::setPositionX(x);
    this->recalculateBounds();
}
void Clickable::setPositionY(float y) {
    Layer::setPositionY(y);
    this->recalculateBounds();
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
    this->recalculateBounds();
}

void Clickable::setWidth(float width) {
    this->width = width;
    this->recalculateBounds();
}

void Clickable::setHeight(float height) {
    this->height = height;
    this->recalculateBounds();
}

void Clickable::setVisible(bool visible) {
    Layer::setVisible(visible);
    this->setEnabled(visible);
}

}
