#include "ProgressIndicatorLayer.h"

namespace QUAT {

void ProgressIndicatorLayer::update(int currentRank, float progressPercent) {
  this->displayRank(currentRank);
  this->setProgressPercent(progressPercent);
}

void ProgressIndicatorLayer::displayRank(int currentRank) {
   this->leftText->setString(std::to_string(currentRank));
   this->rightText->setString(std::to_string(currentRank + 1));
}

void ProgressIndicatorLayer::setProgressPercent(float percent) {
  this->progress->setPercent(percent);
}

bool ProgressIndicatorLayer::init() {
	// Init the super class
  if ( !cocos2d::Layer::init() )
  {
      return false;
  }

  float textSize = fontSize * 0.3,
        xOffset  = barWidth * 0.1;

  // Set the default color
  this->defaultColor = new cocos2d::Color4B(255,255,255,64);
  this->fillInColor = new cocos2d::Color4B(255,255,255,120);

  this->progress = ProgressBar::create(barWidth, fontSize * 0.2);
  this->progress->setBackgroundColor(*this->fillInColor);
  this->progress->setForegroundColor(cocos2d::Color4B::WHITE);
  this->progress->setPercent(0.6);
  this->addChild(this->progress, 1);

  this->leftText = cocos2d::Label::createWithTTF("1", Q_FONT_PATH, textSize);
  this->leftText->setPositionX(-1 * (barWidth / 2) - xOffset);
  this->addChild(this->leftText, 2);

  this->rightText = cocos2d::Label::createWithTTF("2", Q_FONT_PATH, textSize);
  this->rightText->setPositionX((barWidth / 2) + xOffset);
  this->addChild(this->rightText, 2);

	return true;
}


ProgressIndicatorLayer::ProgressIndicatorLayer(float fontSize, float barWidth) {
    this->fontSize = fontSize;
    this->barWidth = barWidth;
}


ProgressIndicatorLayer * ProgressIndicatorLayer::create(float fontSize, float barWidth)
{
    ProgressIndicatorLayer *pRet = new(std::nothrow) ProgressIndicatorLayer(fontSize, barWidth);
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
