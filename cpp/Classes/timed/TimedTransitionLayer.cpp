#include "TimedTransitionLayer.h"

namespace QUAT {


TimedTransitionLayer * TimedTransitionLayer::create(cocos2d::Rect * gameBounds)
{
    TimedTransitionLayer *pRet = new(std::nothrow) TimedTransitionLayer(gameBounds);
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

TimedTransitionLayer::TimedTransitionLayer(cocos2d::Rect * gameBounds) {
    this->gameBounds = gameBounds;
}

bool TimedTransitionLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  float width          = gameBounds->size.width,
        height         = gameBounds->size.height,
        circleSize     = height / 6,
        circleFontSize = circleSize * 0.8;
  
  // The circle that animates the time remaining in the combo
  this->circle = CircleNode::create(circleSize);
  this->circle->setColor(cocos2d::Color4B(255, 255, 255, 40));
  this->circle->setPosition(width / 2, height / 2);
  this->addChild(this->circle, 2);

  return true;
}

}

