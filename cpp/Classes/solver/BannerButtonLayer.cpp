#include "BannerButtonLayer.h"

namespace QUAT {
void BannerButtonLayer::up() {
	cocos2d::log("test");
}

void BannerButtonLayer::entered() {
}
void BannerButtonLayer::left() {
}
bool BannerButtonLayer::init() {
	// Init the super class
    if ( !Clickable::init() )
    {
        return false;
    }

    // Initialize the background
    this->background = cocos2d::Sprite::create("banner.png");

    this->enterCallback = CC_CALLBACK_0(BannerButtonLayer::entered, this);
    this->leaveCallback = CC_CALLBACK_0(BannerButtonLayer::left, this);

    // Rescale it to the proper size
    float height = this->_height,
    	  width = height * 0.52,
    	  scale = height / this->background->getBoundingBox().size.height;

    this->background->setScale(scale,scale);
    this->background->setPositionX(width / 2);
    this->background->setPositionY(height / 2);
    this->addChild(this->background, 1);

    this->textLabel = cocos2d::Label::createWithTTF("20", "fonts/Arimo-Regular.ttf", height * 0.3);
    this->textLabel->setPositionX(width / 2);
    this->textLabel->setPositionY(height * 0.58);
    this->addChild(this->textLabel, 2);

    // Set up the bounds
    this->setHeight(height);
    this->setWidth(width);

	return true;
}


BannerButtonLayer::BannerButtonLayer(float height) {
	this->_height = height;
}

void BannerButtonLayer::updateText() {
    this->textLabel->setString(std::to_string(this->value));
}

void BannerButtonLayer::rankDown(int toVal) {
    this->value = toVal;

    auto moveUp = cocos2d::Sequence::create(
        cocos2d::MoveTo::create(0.75, cocos2d::Vec2(this->getPositionX(), this->getPositionY() + this->_height)),
        // Updates the text
        cocos2d::CallFunc::create( CC_CALLBACK_0(BannerButtonLayer::updateText, this)),
        cocos2d::MoveTo::create(0.75, cocos2d::Vec2(this->getPositionX(), this->getPositionY())),
         nullptr
    );
    
    this->runAction(moveUp);
}

void BannerButtonLayer::update(int newVal) {
    if (newVal < this->value) {
        this->rankDown(newVal);
    }
}

BannerButtonLayer * BannerButtonLayer::create(float height)
{
    BannerButtonLayer *pRet = new(std::nothrow) BannerButtonLayer(height);
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