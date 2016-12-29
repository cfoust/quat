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
}



bool TimedLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  // Records the total height of the layer
  float totalHeight    = 0,
        padding        = sectionWidth * 0.05,
        buttonWidth    = sectionWidth * 0.2,
        buttonHeight   = sectionHeight,
        buttonFontSize = fontSize * 0.3,
        cardWidth      = (sectionWidth - buttonWidth - padding),
        cardHeight     = sectionHeight;

  // Add a nice header
  auto headerLabel = cocos2d::Label::createWithTTF("TIMED MODE", Q_FONT_PATH, buttonFontSize);
  headerLabel->setPositionX(sectionWidth * 0.15);
  headerLabel->setPositionY(sectionHeight + (buttonFontSize / 2));
  this->addChild(headerLabel);

  // Full size continue button
  this->continueButton = MenuButton::create("Continue", buttonFontSize, buttonWidth, buttonHeight);
  this->continueButton->setPositionX(cardWidth + padding);
  this->addChild(this->continueButton);

  // Calculate size of the smaller buttons
  float smallButtonHeight = (sectionHeight - padding) / 2;

  // Make two smaller buttons for when the user already has a run going
  this->restartButton = MenuButton::create("Restart", buttonFontSize, buttonWidth, smallButtonHeight);
  this->restartButton->setPositionX(cardWidth + padding);
  this->addChild(this->restartButton);

  this->continueTopButton = MenuButton::create("Continue", buttonFontSize, buttonWidth, smallButtonHeight);
  this->continueTopButton->setPositionX(cardWidth + padding);
  this->continueTopButton->setPositionY(smallButtonHeight + padding);
  this->addChild(this->continueTopButton);
  
  // Create the section
  this->card = TimedCard::create(fontSize, cardWidth, cardHeight);
  this->addChild(this->card);

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

