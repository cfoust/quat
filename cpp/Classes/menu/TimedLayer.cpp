#include "TimedLayer.h"


namespace QUAT {


TimedLayer * TimedLayer::create(float fontSize,
                                    float cardWidth,
                                    float cardHeight)
{
    TimedLayer *pRet = new(std::nothrow) TimedLayer(fontSize, cardWidth, cardHeight);
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
  auto user = game->getUser();
}


bool TimedLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  // Records the total height of the layer
  float totalHeight    = 0,
        buttonFontSize = fontSize * 0.4,
        buttonWidth    = cardWidth * 0.4,
        buttonHeight   = cardHeight * 0.3,
        padding        = cardHeight * 0.1;

  this->continueButton = MenuButton::create("Continue", buttonFontSize, buttonWidth, buttonHeight, NULL);
  this->continueButton->setPositionX((cardWidth - buttonWidth) / 2);
  this->addChild(this->continueButton);
  totalHeight += buttonHeight + padding;
  
  // Create the card
  this->card = TimedCard::create(fontSize, cardWidth, cardHeight);
  this->card->setPositionY(totalHeight);
  this->addChild(this->card);
  totalHeight += cardHeight + padding * 2;

  // Add a nice header
  auto headerLabel = cocos2d::Label::createWithTTF("Timed Mode", Q_FONT_PATH, buttonFontSize);
  headerLabel->setPositionX(cardWidth / 2);
  headerLabel->setPositionY(totalHeight);
  this->addChild(headerLabel);
  totalHeight += buttonFontSize;

  this->setContentSize(cocos2d::Size(cardWidth,
                                     totalHeight));

  // Indicates we initialized successfully
  return true;
}

TimedLayer::TimedLayer(float fontSize,
                           float cardWidth,
                           float cardHeight) {
  this->fontSize = fontSize;
  this->cardWidth = cardWidth;
  this->cardHeight = cardHeight;
}



}

