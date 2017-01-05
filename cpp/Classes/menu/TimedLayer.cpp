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

  // Score for rank 2
  if (state->getHighScore(2) > 0) {
    this->time2Label->setString(TimeUtils::formatMs(state->getHighScore(2)));
  } else {
    this->time2Label->setString(TIME_DEFAULT);
  }

  // Score for rank 4
  if (state->getHighScore(4) > 0) {
    this->time4Label->setString(TimeUtils::formatMs(state->getHighScore(4)));
  } else {
    this->time4Label->setString(TIME_DEFAULT);
  }

  // Score for rank 8
  if (state->getHighScore(8) > 0) {
    this->time8Label->setString(TimeUtils::formatMs(state->getHighScore(8)));
  } else {
    this->time8Label->setString(TIME_DEFAULT);
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
        cardWidth      = (sectionWidth - buttonWidth - padding),
        cardHeight     = sectionHeight;

  // Add a nice header
  this->headerLabel = cocos2d::Label::createWithTTF("TIMED", Q_FONT_PATH, buttonFontSize);
  headerLabel->setPositionX(cardWidth / 2);
  headerLabel->setPositionY(sectionHeight + (buttonFontSize * 0.75));
  this->addChild(headerLabel);

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

  // Add all of the high score text labels
  float bestFontSize   = fontSize * 0.5,
        bestFontPadding = bestFontSize * 1.4,
        rankLeftPos = sectionWidth * 0.2,
        timeLeftPos = sectionWidth * 0.45,
        halfSection = sectionHeight / 2;

  this->rank2Label = cocos2d::Label::createWithTTF("2", Q_FONT_PATH, bestFontSize);
  this->rank2Label->setPositionX(rankLeftPos);
  this->addChild(rank2Label);

  this->rank4Label = cocos2d::Label::createWithTTF("4", Q_FONT_PATH, bestFontSize);
  this->rank4Label->setPositionX(rankLeftPos);
  this->addChild(rank4Label);

  this->rank8Label = cocos2d::Label::createWithTTF("8", Q_FONT_PATH, bestFontSize);
  this->rank8Label->setPositionX(rankLeftPos);
  this->addChild(rank8Label);

  this->time2Label = cocos2d::Label::createWithTTF(TIME_DEFAULT, Q_FONT_PATH, bestFontSize);
  this->time2Label->setPositionX(timeLeftPos);
  this->addChild(time2Label);

  this->time4Label = cocos2d::Label::createWithTTF(TIME_DEFAULT, Q_FONT_PATH, bestFontSize);
  this->time4Label->setPositionX(timeLeftPos);
  this->addChild(time4Label);

  this->time8Label = cocos2d::Label::createWithTTF(TIME_DEFAULT, Q_FONT_PATH, bestFontSize);
  this->time8Label->setPositionX(timeLeftPos);
  this->addChild(time8Label);

  this->rank2Label->setPositionY(halfSection + bestFontPadding);
  this->rank4Label->setPositionY(halfSection);
  this->rank8Label->setPositionY(halfSection - bestFontPadding);

  this->time2Label->setPositionY(halfSection + bestFontPadding);
  this->time4Label->setPositionY(halfSection);
  this->time8Label->setPositionY(halfSection - bestFontPadding);

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

