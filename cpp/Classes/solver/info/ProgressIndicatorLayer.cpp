#include "ProgressIndicatorLayer.h"

namespace QUAT {

void ProgressIndicatorLayer::updateFromModel(Game * game) {
  auto user  = game->getUser();
  auto state = game->getState();

  // Update the percentage of the current rank
  this->setProgressPercent(state->getRankProgress()); 

  // Update the rank
  int rank = state->getDisplayRank();
  this->displayRank(rank);

  // If we're in timed mode, show the star on the finish rank
  if (!user->isPlayingEndless()) {
    int upper = rank + 1,
        goal  = user->getTimedState()->getWinRank();

    this->rightStar->setVisible(upper == goal);
    this->rightText->setVisible(upper != goal);
    this->rightText->setString(std::to_string(upper));
  }
}

void ProgressIndicatorLayer::animate() {
  // Stop all of the actions
	leftText->stopAllActions();
	rightText->stopAllActions();
	progress->stopAllActions();

  // Reset the opacity
  this->setOpacity(0);

	auto fade = cocos2d::Sequence::create(cocos2d::FadeTo::create(Q_TEXT_INDICATOR_FADE, 255),
								   cocos2d::DelayTime::create(Q_TEXT_INDICATOR_FADE),
								   cocos2d::FadeTo::create(Q_TEXT_INDICATOR_FADE, 0),
								   nullptr);

  leftText->runAction(fade);
  rightText->runAction(fade->clone());
  progress->runAction(fade->clone());
}

void ProgressIndicatorLayer::displayRank(int currentRank) {
   this->leftText->setString(std::to_string(currentRank));

   int upper = currentRank + 1;
   this->rightStar->setVisible(upper == 13);
   this->rightText->setVisible(upper != 13);
   this->rightText->setString(std::to_string(upper));
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

  float yOffset = textSize * 0.05;

  this->leftText = cocos2d::Label::createWithTTF("1", Q_FONT_PATH, textSize);
  this->leftText->setPositionX(-1 * (barWidth / 2) - xOffset);
  this->leftText->setPositionY(yOffset);
  this->addChild(this->leftText, 2);

  float rightPosition = (barWidth / 2) + (xOffset * 0.8);
  this->rightText = cocos2d::Label::createWithTTF("2", Q_FONT_PATH, textSize);
  this->rightText->setPositionX(rightPosition);
  this->rightText->setPositionY(yOffset);
  this->addChild(this->rightText, 2);

  // Creates a string for the star
  this->rightStar = IconNode::create(ICON_STAR, textSize);
  this->rightStar->setPositionX(rightPosition);
  this->rightStar->setPositionY(yOffset);
  this->addChild(this->rightStar, 2);

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

void ProgressIndicatorLayer::setOpacity(GLubyte opacity) {
  cocos2d::Layer::setOpacity(opacity);
  this->leftText->setOpacity(opacity);
  this->rightText->setOpacity(opacity);
  this->progress->setOpacity(opacity);
}

}
