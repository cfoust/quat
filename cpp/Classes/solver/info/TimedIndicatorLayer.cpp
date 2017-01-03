#include "TimedIndicatorLayer.h"

namespace QUAT {


void TimedIndicatorLayer::updateFromModel(Game * game) {
  auto state = game->getUser()->getTimedState();

  // Update the time string
  this->timer->setString(std::to_string(state->getTime()));
}

bool TimedIndicatorLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  auto gameBounds = this->gameBounds;

  float timerSize = this->fontSize * Q_TEXT_INDICATOR_FONT;
  this->timer = cocos2d::Label::createWithTTF("00:00.000", Q_FONT_PATH, timerSize);
  this->timer->setPosition(gameBounds->size.width / 2, gameBounds->size.height / 2);
  this->addChild(this->timer);

	return true;
}


TimedIndicatorLayer::TimedIndicatorLayer(Rect * gameBounds, float fontSize) {
    this->fontSize = fontSize;
    this->gameBounds = gameBounds;
}


TimedIndicatorLayer * TimedIndicatorLayer::create(Rect * gameBounds, float fontSize)
{
    TimedIndicatorLayer *pRet = new(std::nothrow) TimedIndicatorLayer(gameBounds, fontSize);
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
