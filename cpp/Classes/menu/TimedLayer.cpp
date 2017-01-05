#include "TimedLayer.h"


namespace QUAT {


TimedLayer * TimedLayer::create(float fontSize,
                                    float sectionWidth,
                                    float sectionHeight)
{
    TimedLayer *pRet = new(std::nothrow) TimedLayer(fontSize, sectionWidth, sectionHeight);
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

void TimedLayer::updateFromModel(Game * game) {
  auto state = game->getUser()->getTimedState();

  // Hide and show the buttons if necessary
  bool canContinue = state->canContinue();
  this->playButton->setVisible(!canContinue);
  this->continueTopButton->setVisible(canContinue);
  this->restartButton->setVisible(canContinue);

  unsigned long score = state->getHighScore(state->getWinRank());
  if (score > 0) {
    this->highScoreLabel->setString(TimeUtils::formatMs(score));
  } else {
    this->highScoreLabel->setString("?:??:??.???");
  }
}



bool TimedLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  // Records the total height of the layer
  float padding        = sectionWidth * 0.05,
        buttonWidth    = sectionWidth * 0.2,
        buttonHeight   = sectionHeight,
        buttonFontSize = fontSize * 0.3,
        bestFontSize   = fontSize,
        cardWidth      = (sectionWidth - buttonWidth - padding),
        cardHeight     = sectionHeight;

  // Add a nice header
  this->headerLabel = cocos2d::Label::createWithTTF("TIMED", Q_FONT_PATH, buttonFontSize);
  headerLabel->setPositionX(cardWidth / 2);
  headerLabel->setPositionY(sectionHeight + (buttonFontSize * 0.75));
  this->addChild(headerLabel);

  // Add the high score label
  this->highScoreLabel = cocos2d::Label::createWithTTF("?:??:??.???", Q_FONT_PATH, bestFontSize);
  highScoreLabel->setPositionX(cardWidth / 2);
  highScoreLabel->setPositionY(sectionHeight * 0.3);
  this->addChild(highScoreLabel);

  // Create the section
  this->card = TimedCard::create(fontSize, cardWidth, cardHeight);
  this->addChild(this->card);

  float borderRadius = this->card->getBorderRadius(),
        borderWidth  = this->card->getBorderWidth();

  // Calculate size of the smaller buttons
  float smallButtonHeight     = (sectionHeight - padding) / 2,
        smallButtonIconHeight = smallButtonHeight * 0.5;

  // Full size continue button
  this->playButton = IconMenuButton::create("skip.png",
                                        smallButtonIconHeight,
                                        buttonWidth,
                                        buttonHeight,
                                        borderRadius,
                                        borderWidth);
  this->playButton->setPositionX(cardWidth + padding);
  this->addChild(this->playButton);

  // Make two smaller buttons for when the user already has a run going
  this->restartButton = IconMenuButton::create("undo.png",
                                           smallButtonIconHeight,
                                           buttonWidth,
                                           smallButtonHeight,
                                           borderRadius,
                                           borderWidth);
  this->restartButton->setPositionX(cardWidth + padding);
  this->addChild(this->restartButton);

  this->continueTopButton = IconMenuButton::create("skip.png",
                                               smallButtonIconHeight,
                                               buttonWidth,
                                               smallButtonHeight,
                                               borderRadius,
                                               borderWidth);
  this->continueTopButton->setPositionX(cardWidth + padding);
  this->continueTopButton->setPositionY(smallButtonHeight + padding);
  this->addChild(this->continueTopButton);

  this->setContentSize(cocos2d::Size(sectionWidth,
                                     sectionHeight + padding));

  // Indicates we initialized successfully
  return true;
}

TimedLayer::TimedLayer(float fontSize,
                           float sectionWidth,
                           float sectionHeight) {
  this->fontSize = fontSize;
  this->sectionWidth = sectionWidth;
  this->sectionHeight = sectionHeight;
}



}

