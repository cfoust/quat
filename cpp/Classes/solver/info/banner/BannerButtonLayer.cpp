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

    // Initialize the text label which shows the rank text
    this->textLabel = cocos2d::Label::createWithTTF("20", Q_FONT_PATH, height * Q_BANNER_FONT);
    this->textLabel->setPositionX(width / 2);
    this->textLabel->setPositionY(height * Q_BANNER_RANK_Y);
    this->addChild(this->textLabel, 2);

    // Creates the draw node that's used for the rank up animation
    this->circle = ExplodingCircle::create();
    this->circle->setPositionX(width / 2);
    this->circle->setPositionY(height / 2);
    this->circle->setOpacity(0);
    this->addChild(this->circle);

    this->value = -1;

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

void BannerButtonLayer::animateChange(int toVal) {
    this->value = toVal;

    auto moveUp = cocos2d::Sequence::create(
        cocos2d::MoveTo::create(Q_BANNER_SLIDE, cocos2d::Vec2(this->getPositionX(), this->getPositionY() + this->_height * 1.2)),
        // Updates the text
        cocos2d::CallFunc::create( CC_CALLBACK_0(BannerButtonLayer::updateText, this)),
        cocos2d::MoveTo::create(Q_BANNER_SLIDE, cocos2d::Vec2(this->getPositionX(), this->getPositionY())),
         nullptr
    );

    this->runAction(moveUp);
}

void BannerButtonLayer::rankUp(int toVal) {
    this->animateChange(toVal);

    // Reset the scale and the opacity of the circle
    this->circle->setScale(0.01);
    this->circle->setOpacity(255);

    // The simultaneous growth and fade of the exploding circle
    auto spawn = cocos2d::Spawn::create(
        cocos2d::FadeOut::create(Q_BANNER_EXPLODE),
        cocos2d::ScaleTo::create(Q_BANNER_EXPLODE, 200),
        nullptr
    );

    // The sequence that makes it happen after the banner has finished
    // animating
    auto wait = cocos2d::Sequence::create(
        cocos2d::DelayTime::create(Q_BANNER_SLIDE * 2),
        spawn,
        nullptr
    );

    
    this->circle->runAction(wait);
    
}
void BannerButtonLayer::rankDown(int toVal) {
    this->animateChange(toVal);
}

void BannerButtonLayer::update(int newVal) {
    // Handle the case where the game was just loaded
    if (this->value == -1) {
        this->value = newVal;
        this->updateText();
        return;
    }

    if (newVal < this->value) {
        this->rankDown(newVal);
    }
    else if (newVal > this->value) {
        this->rankUp(newVal);
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
