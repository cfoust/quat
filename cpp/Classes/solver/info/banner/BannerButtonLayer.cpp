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
    this->textLabel = cocos2d::Label::createWithTTF("20", "fonts/Arimo-Regular.ttf", height * 0.3);
    this->textLabel->setPositionX(width / 2);
    this->textLabel->setPositionY(height * 0.58);
    this->addChild(this->textLabel, 2);

    // Creates the draw node that's used for the rank up animation
    this->node = cocos2d::DrawNode::create();
    this->node->setPositionX(width / 2);
    this->node->setPositionY(height / 2);
    this->addChild(this->node);

    // Fills the node with a circle
    this->node->drawSolidCircle( cocos2d::Vec2(0,0), 40, CC_DEGREES_TO_RADIANS(360), 50, cocos2d::Color4F::WHITE);

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
        cocos2d::MoveTo::create(0.75, cocos2d::Vec2(this->getPositionX(), this->getPositionY() + this->_height)),
        // Updates the text
        cocos2d::CallFunc::create( CC_CALLBACK_0(BannerButtonLayer::updateText, this)),
        cocos2d::MoveTo::create(0.75, cocos2d::Vec2(this->getPositionX(), this->getPositionY())),
         nullptr
    );

    this->runAction(moveUp);
}

void BannerButtonLayer::rankUp(int toVal) {
    this->animateChange(toVal);

    // this->node->setScale(0.01);
    this->node->setOpacity(128);

    auto spawn = cocos2d::Spawn::create(
        cocos2d::FadeOut::create(0.75),
        cocos2d::ScaleTo::create(0.75, 200),
        nullptr
    );

    
    // this->node->runAction(spawn);
    
}
void BannerButtonLayer::rankDown(int toVal) {
    this->animateChange(toVal);
}

void BannerButtonLayer::update(int newVal) {
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