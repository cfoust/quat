#include "EndlessLayer.h"


namespace QUAT {


EndlessLayer * EndlessLayer::create(float fontSize,
                                    float sectionWidth,
                                    float sectionHeight)
{
    EndlessLayer *pRet = new(std::nothrow) EndlessLayer(fontSize, sectionWidth, sectionHeight);
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

void EndlessLayer::updateFromModel(Game * game) {
  this->card->updateFromModel(game);
}


bool EndlessLayer::init() {
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
  auto headerLabel = cocos2d::Label::createWithTTF("ENDLESS MODE", Q_FONT_PATH, buttonFontSize);
  headerLabel->setPositionX(sectionWidth * 0.15);
  headerLabel->setPositionY(sectionHeight + (buttonFontSize / 2));
  this->addChild(headerLabel);

  this->continueButton = MenuButton::create("Continue", buttonFontSize, buttonWidth, buttonHeight);
  this->continueButton->setPositionX(cardWidth + padding);
  this->addChild(this->continueButton);
  
  // Create the section
  this->card = RankCard::create(fontSize, cardWidth, cardHeight);
  this->addChild(this->card);

  this->setContentSize(cocos2d::Size(sectionWidth,
                                     sectionHeight + padding));

  // Indicates we initialized successfully
  return true;
}

EndlessLayer::EndlessLayer(float fontSize,
                           float sectionWidth,
                           float sectionHeight) {
  this->fontSize = fontSize;
  this->sectionWidth = sectionWidth;
  this->sectionHeight = sectionHeight;
}



}

