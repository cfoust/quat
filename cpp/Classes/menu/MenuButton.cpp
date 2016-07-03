#include "MenuButton.h"

#include <string>

USING_NS_CC;

namespace QUAT {


/**
* Sets the enabled status of the button. Enabled buttons can receive
* events.
*/
void MenuButton::enabled(bool status) {
    this->_enabled = status;
}

/**
* Returns whether or not the button is enabled.
*/
bool MenuButton::isEnabled() {
    return this->_enabled;
}

/**
* Sets the selected status of the button. Selected means that the border
* is highlighted.
*/
void MenuButton::selected(bool selected) {
    this->background->setColor(selected ? *this->selectedColor : *this->defaultColor);
    this->_selected = selected;
}


bool MenuButton::isSelected() {
    return this->_selected;
}

void MenuButton::showBorder(bool showBorder) {
    this->border->setVisible(showBorder);
    this->background->setVisible(showBorder);
}

/**
* Sets the text of the button.
*/
void MenuButton::setText(std::string text) {
    this->textLabel->setString(text);
}

MenuButton * MenuButton::create(std::string title, 
               float fontSize, 
               float width, 
               float height,
               std::function<void(void)> callback)
{
    MenuButton *pRet = new(std::nothrow) MenuButton(title, 
                                                    fontSize, 
                                                    width, 
                                                    height,
                                                    callback);
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


bool MenuButton::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }

    this->textLabel = cocos2d::Label::createWithTTF(this->title, "fonts/Ubuntu.ttf", this->fontSize);
    this->textLabel->setPositionX(this->width / 2);
    this->textLabel->setPositionY(this->height / 2);
    this->addChild(this->textLabel, 2);

    this->bounds = new cocos2d::Rect(0,0,0,0);

    this->defaultColor = new cocos2d::Color4B(255,255,255,64);
    this->selectedColor = new cocos2d::Color4B(255,255,255,153);

    float borderRadius = this->fontSize * 0.3,
          borderWidth = this->fontSize * 0.18;

    this->border = RectRadius::create(this->width, this->height, borderRadius, borderWidth, false);
    this->border->setPositionX(this->width / 2);
    this->border->setPositionY(this->height / 2);
    this->border->setColor(cocos2d::Color4B::WHITE);
    this->addChild(this->border, 1);

    this->background = RectRadius::create(this->width, this->height, borderRadius, borderWidth, true);
    this->background->setPositionX(this->width / 2);
    this->background->setPositionY(this->height / 2);
    this->background->setColor(*this->defaultColor);
    this->addChild(this->background, 0);
    
    //Create a "one by one" touch event listener (processes one touch at a time)
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    touchListener->setSwallowTouches(false);

    touchListener->onTouchBegan = CC_CALLBACK_2(MenuButton::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(MenuButton::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(MenuButton::onTouchEnded, this);

     _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


    this->regenerateBounds();

    return true;
}

MenuButton::MenuButton(std::string title, 
               float fontSize, 
               float width, 
               float height,
               std::function<void(void)> callback) {
    this->title = title;
	this->fontSize = fontSize;
    this->width = width;
    this->height = height;
    this->callback = callback;
    this->_enabled = true;
    this->_trackingTouch = false;
}

void MenuButton::regenerateBounds() {
    this->bounds->setRect(this->getPositionX(), this->getPositionY(), this->width, this->height);
}

void MenuButton::setPositionX(float x) {
    cocos2d::Layer::setPositionX(x);
    this->regenerateBounds();
}
void MenuButton::setPositionY(float y) {
    cocos2d::Layer::setPositionY(y);
    this->regenerateBounds();
}

bool MenuButton::contains(cocos2d::Touch* touch) {
    return this->bounds->containsPoint(touch->getLocation());
}

bool MenuButton::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!this->_enabled) {
        return false;
    }

    if (!this->contains(touch)) {
        return false;
    }

    if (this->_trackingTouch) {
        return false;
    } else {
        this->_trackingTouch = true;
    }
    this->selected(true);
    return true;
}
void MenuButton::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    bool inside = this->contains(touch);
    if (this->_trackingTouch && !inside) {
        this->_trackingTouch = false;
        this->selected(false);
    } else if (!this->_trackingTouch && inside) {
        this->_trackingTouch = true;
        this->selected(true);
    }
}
void MenuButton::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    this->selected(false);
    if (this->contains(touch)) {
        this->callback();
    }
    this->_trackingTouch = false;
}

}