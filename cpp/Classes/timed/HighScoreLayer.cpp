#include "HighScoreLayer.h"

namespace QUAT {


HighScoreLayer * HighScoreLayer::create(cocos2d::Rect * gameBounds,
                       GameStateController * GSC)
{
    HighScoreLayer *pRet = new(std::nothrow) HighScoreLayer(gameBounds, GSC);
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

void HighScoreLayer::updateFromModel(Game * game) {
  auto state = game->getUser()->getTimedState();

  this->scoreText->setString(TimeUtils::formatMs(state->getTime()));
}

HighScoreLayer::HighScoreLayer(cocos2d::Rect * gameBounds,
                       GameStateController * GSC) {
  this->gameBounds = gameBounds;
  this->GSC = GSC;
}

bool HighScoreLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  float width          = gameBounds->size.width,
        height         = gameBounds->size.height,
        fontSize       = height * 0.08;

  this->scoreText = cocos2d::Label::createWithTTF(TimeUtils::formatMs(65123), Q_FONT_PATH, fontSize);
  this->scoreText->setPosition(width / 2, height * 0.6);
  this->scoreText->setColor(cocos2d::Color3B::WHITE);
  this->addChild(this->scoreText);

  return true;
}


}

