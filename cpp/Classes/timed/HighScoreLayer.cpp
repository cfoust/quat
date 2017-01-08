#include "HighScoreLayer.h"

namespace QUAT {


HighScoreLayer * HighScoreLayer::create(Game * game,
                                        cocos2d::Rect * gameBounds,
                                        GameStateController * GSC)
{
    HighScoreLayer *pRet = new(std::nothrow) HighScoreLayer(game, gameBounds, GSC);
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

void HighScoreLayer::updateFromModel() {
  auto state = game->getUser()->getTimedState();

  // Set the time the user completed the challenge in
  this->scoreText->setString(TimeUtils::formatMs(state->getTime()));

  // Set up the banner
  this->banner->update(state->getWinRank());
}

void HighScoreLayer::restartCallback() {
  auto user = game->getUser();

  // Reset the state of timed mode
  user->getTimedState()->reset();

  // Move to the puzzle solver state
  this->GSC->setState(S_TimedTransition);
}


HighScoreLayer::HighScoreLayer(Game * game,
                               cocos2d::Rect * gameBounds,
                               GameStateController * GSC) {
  this->game = game;
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
        fontSize       = height * 0.10;

  // The text that shows the time the user completed at
  this->scoreText = cocos2d::Label::createWithTTF(TimeUtils::formatMs(1000 * 60 * 61), Q_FONT_PATH, fontSize);
  this->scoreText->setPosition(width / 2, height * 0.65);
  this->scoreText->setOpacity(65);
  this->addChild(this->scoreText);

  float bannerWidth  = width * 0.2,
        bannerHeight = height * 0.15;
  auto fillIn  = new cocos2d::Color4B(255,255,255,120);

  // The banner that shows the goal rank
  this->banner = DrawnBanner::create(bannerWidth, bannerHeight, fillIn);
  this->banner->setPositionX((width / 2) - bannerWidth / 2);
  this->banner->setPositionY(height - bannerHeight);
  this->addChild(this->banner, 1);

  // The restart button to try again
  float buttonWidth         = width * 0.4,
        buttonHeight        = buttonWidth * 0.3,
        buttonIconHeight    = buttonHeight * 0.6,
        borderRadius        = 0.05 * buttonWidth,
        borderWidth         = 0.01 * buttonWidth;

  this->restartButton = IconMenuButton::create("undo.png",
                                           buttonIconHeight,
                                           buttonWidth,
                                           buttonHeight,
                                           borderRadius,
                                           borderWidth);
  this->restartButton->setPositionX((width / 2) - (buttonWidth / 2));
  this->restartButton->setPositionY(height * 0.1);
  this->addChild(this->restartButton);
  this->restartButton->upCallback = CC_CALLBACK_0(HighScoreLayer::restartCallback, this);

  return true;
}


}

