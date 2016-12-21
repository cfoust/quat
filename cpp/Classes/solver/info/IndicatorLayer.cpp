#include "IndicatorLayer.h"

namespace QUAT {

void IndicatorLayer::done() {
  this->text->setString(std::string("Done!"));

  // Stop the actions of the nodes
	this->text->stopAllActions();
  this->doneSprite->stopAllActions();

  // Reset their opacity
	this->text->setOpacity(0);
  this->doneSprite->setOpacity(0);

	auto fade = cocos2d::Sequence::create(cocos2d::FadeTo::create(Q_TEXT_INDICATOR_FADE, 255),
								   cocos2d::DelayTime::create(Q_TEXT_INDICATOR_FADE),
								   cocos2d::FadeTo::create(Q_TEXT_INDICATOR_FADE, 0),
								   nullptr);

	this->text->runAction(fade->clone());
  this->doneSprite->runAction(fade);
}

void IndicatorLayer::perfect() {
  this->text->setString(std::string("Perfect!"));

  // Stop the actions of the nodes
	this->text->stopAllActions();
  this->perfectSprite->stopAllActions();

  // Reset their opacity
	this->text->setOpacity(0);
  this->perfectSprite->setOpacity(0);

	auto fade = cocos2d::Sequence::create(cocos2d::FadeTo::create(Q_TEXT_INDICATOR_FADE, 255),
								   cocos2d::DelayTime::create(Q_TEXT_INDICATOR_FADE),
								   cocos2d::FadeTo::create(Q_TEXT_INDICATOR_FADE, 0),
								   nullptr);

	this->text->runAction(fade->clone());
  this->perfectSprite->runAction(fade);
}

void IndicatorLayer::notAWord(std::string word) {
  this->text->setString(word + std::string(" is not a word"));

  // Stop the actions of the nodes
	this->text->stopAllActions();

  // Reset their opacity
	this->text->setOpacity(0);

	auto fade = cocos2d::Sequence::create(cocos2d::FadeTo::create(Q_TEXT_INDICATOR_FADE, 255),
								   cocos2d::DelayTime::create(Q_TEXT_INDICATOR_FADE),
								   cocos2d::FadeTo::create(Q_TEXT_INDICATOR_FADE, 0),
								   nullptr);

	this->text->runAction(fade);
}

bool IndicatorLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  auto gameBounds = this->gameBounds;

  float textSize = this->fontSize * Q_TEXT_INDICATOR_FONT;
  this->text = cocos2d::Label::createWithTTF("Done!", Q_FONT_PATH, textSize);
  this->text->setOpacity(0);
  this->text->enableItalics();
  this->addChild(this->text);

  // Initialize the sprites
  this->doneSprite = Sprite::create("icons/done.png");
  this->perfectSprite = Sprite::create("icons/perfect.png");

  // Make sure they're scaled properly
  float iconHeight = gameBounds->size.height * 0.1,
        scale = iconHeight / this->doneSprite->getBoundingBox().size.height;
  
  // Adjust things to be a bit smaller
  scale *= 0.8;
  
  // Set up the offset
  float textOffset = textSize + (iconHeight  * .6);

  this->doneSprite->setScale(scale,scale);
  this->doneSprite->setPositionY(textOffset);
  this->doneSprite->setOpacity(0);
  this->addChild(this->doneSprite, 1);

  this->perfectSprite->setScale(scale,scale);
  this->perfectSprite->setPositionY(textOffset * 1.2);
  this->perfectSprite->setOpacity(0);
  this->addChild(this->perfectSprite, 1);

	return true;
}


IndicatorLayer::IndicatorLayer(Rect * gameBounds, float fontSize) {
    this->fontSize = fontSize;
    this->gameBounds = gameBounds;
}


IndicatorLayer * IndicatorLayer::create(Rect * gameBounds, float fontSize)
{
    IndicatorLayer *pRet = new(std::nothrow) IndicatorLayer(gameBounds, fontSize);
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
