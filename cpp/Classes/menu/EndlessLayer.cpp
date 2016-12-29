#include "EndlessLayer.h"


namespace QUAT {


EndlessLayer * EndlessLayer::create(float fontSize,
                                    float cardWidth,
                                    float cardHeight)
{
    EndlessLayer *pRet = new(std::nothrow) EndlessLayer(fontSize, cardWidth, cardHeight);
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
  auto user = game->getUser();
  this->card->update(user->getDisplayRank(), user->getRankProgress());
}


bool EndlessLayer::init() {
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

  // Add a nice header
  auto headerLabel = cocos2d::Label::createWithTTF("Endless Mode", Q_FONT_PATH, buttonFontSize);
  headerLabel->setPositionX(cardWidth / 4);
  headerLabel->setPositionY(buttonHeight / 2);
  this->addChild(headerLabel);

  this->continueButton = MenuButton::create("Continue", buttonFontSize, buttonWidth, buttonHeight, NULL);
  this->continueButton->setPositionX((cardWidth / 2) + (((cardWidth / 2)- buttonWidth) / 2));
  this->addChild(this->continueButton);
  totalHeight += buttonHeight + padding;
  
  // Create the card
  this->card = RankCard::create(fontSize, cardWidth, cardHeight);
  this->card->setPositionY(totalHeight);
  this->addChild(this->card);
  totalHeight += cardHeight;

  this->setContentSize(cocos2d::Size(cardWidth,
                                     totalHeight));

  // Indicates we initialized successfully
  return true;
}

EndlessLayer::EndlessLayer(float fontSize,
                           float cardWidth,
                           float cardHeight) {
  this->fontSize = fontSize;
  this->cardWidth = cardWidth;
  this->cardHeight = cardHeight;
}



}

