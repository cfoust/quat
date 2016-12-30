#include "TimedTransitionLayer.h"

namespace QUAT {


TimedTransitionLayer * TimedTransitionLayer::create(cocos2d::Rect * gameBounds,
                       Game * game,
                       GameStateController * GSC)
{
    TimedTransitionLayer *pRet = new(std::nothrow) TimedTransitionLayer(gameBounds, game, GSC);
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

TimedTransitionLayer::TimedTransitionLayer(cocos2d::Rect * gameBounds,
                       Game * game,
                       GameStateController * GSC) {
  this->gameBounds = gameBounds;
  this->game = game;
  this->GSC = GSC;
}

void TimedTransitionLayer::reset() {
  this->timeLeft = 3;
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
        circleFontSize = circleSize * 1.6;
  
  // The circle that animates the time remaining in the combo
  this->circle = CircleNode::create(circleSize);
  this->circle->setColor(cocos2d::Color4B(255, 255, 255, 40));
  this->circle->setPosition(width / 2, height / 2);
  this->addChild(this->circle, 2);

  this->topText = cocos2d::Label::createWithTTF("3", Q_FONT_PATH, circleFontSize);
  this->topText->setOpacity(40);
  this->topText->setPosition(width / 2, height / 2);
  this->topText->setColor(cocos2d::Color3B::WHITE);

  this->bottomText = cocos2d::Label::createWithTTF("3", Q_FONT_PATH, circleFontSize);
  this->bottomText->setColor(cocos2d::Color3B::WHITE);
  this->bottomText->setOpacity(40);
  this->bottomText->setPosition(width / 2, height / 2);
  this->addChild(bottomText, 1);

  // Sets up the clipping for the main multiplier text
  auto clip = cocos2d::ClippingNode::create();
  clip->setStencil(this->circle->getNode());
  clip->setInverted(false);
  clip->addChild(this->topText);
  clip->setPosition(width / 2, height / 2);
  this->addChild(clip, 3);
  
  // Get updates
  this->scheduleUpdate();

  return true;
}

void TimedTransitionLayer::update(float delta) {
  if (this->timeLeft > 0) {
    // Add the delta
    this->timeLeft -= delta;

    // Set the circle's text
    int secs = (int) ceil(timeLeft);
    auto secString = std::to_string(secs);
    this->topText->setString(secString);
    this->bottomText->setString(secString);

    // Set the circle's percentage
    this->circle->setPercent(this->timeLeft / TRANS_SECS);

    // Means the addition of the current delta pushed
    // us below zero; this will only run once in a reset
    if (this->timeLeft < 0) {
      this->GSC->setState(S_PuzzleSolver);
    }
  }
}

}

