#include "MenuButton.h"

#include <string>

USING_NS_CC;

namespace QUAT {

void MenuButton::entered() {
    this->selected(true);
}

void MenuButton::left() {
    this->selected(false);
}


void MenuButton::setEnabled(bool enabled) {
    Clickable::setEnabled(enabled);

    // Set the disabled as a proportion of default color
    float ratio = 0.7;
    auto normalBG = this->defaultColor,
         normalBorder = cocos2d::Color4B::WHITE; 

    // The background color
    cocos2d::Color4B adjustedBG(normalBG.r * ratio,
                                   normalBG.g * ratio,
                                   normalBG.b * ratio,
                                   normalBG.a),
    // The border color
                     adjustedBorder(normalBorder.r * ratio,
                                   normalBorder.g * ratio,
                                   normalBorder.b * ratio,
                                   normalBorder.a);

    this->background->setColor(enabled ? normalBG : adjustedBG);
    this->border->setColor(enabled ? normalBorder : adjustedBorder);
    this->textLabel->setTextColor(enabled ? normalBorder : adjustedBorder);
}


/**
* Sets the selected status of the button. Selected means that the border
* is highlighted.
*/
void MenuButton::selected(bool selected) {
    if (!this->enabled && selected) return;
    this->background->setColor(selected ? this->selectedColor : this->defaultColor);
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

const std::string MenuButton::getText() {
    return this->textLabel->getString();
}

MenuButton * MenuButton::create(std::string title,
               float fontSize,
               float width,
               float height)
{
    MenuButton *pRet = new(std::nothrow) MenuButton(title,
                                                    fontSize,
                                                    width,
                                                    height);
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
    if ( !Clickable::init() )
    {
        return false;
    }

    this->setWidth(this->_width);
    this->setHeight(this->_height);

    this->enterCallback = CC_CALLBACK_0(MenuButton::entered, this);
    this->leaveCallback = CC_CALLBACK_0(MenuButton::left, this);

    this->textLabel = cocos2d::Label::createWithTTF(this->title, Q_FONT_PATH, this->fontSize);
    this->textLabel->setPositionX(this->width * 0.48);
    this->textLabel->setPositionY(this->height / 2);
    this->addChild(this->textLabel, 2);

    this->defaultColor = cocos2d::Color4B(255,255,255,64);
    this->selectedColor = cocos2d::Color4B(255,255,255,153);

    float borderRadius = this->fontSize * 0.3,
          borderWidth = this->fontSize * 0.06;

    this->border = RectRadius::create(this->width, this->height, borderRadius, borderWidth, false);
    this->border->setPositionX(this->width / 2);
    this->border->setPositionY(this->height / 2);
    this->border->setColor(cocos2d::Color4B::WHITE);
    this->addChild(this->border, 1);

    this->background = RectRadius::create(this->width, this->height, borderRadius, borderWidth, true);
    this->background->setPositionX(this->width / 2);
    this->background->setPositionY(this->height / 2);
    this->background->setColor(this->defaultColor);
    this->addChild(this->background, 0);

    // This needs to be here because we changed the Clickable API to track from
    // the center of the bounds instead of the bottom-left corner as we used to do
    // when this class was ported over from JS.
    this->setOffset(this->_width / -2, this->_height / -2);

    return true;
}

MenuButton::MenuButton(std::string title,
               float fontSize,
               float width,
               float height) {
    this->title = title;
  	this->fontSize = fontSize;
    this->_width = width;
    this->_height = height;
    this->_enabled = true;
}

}
