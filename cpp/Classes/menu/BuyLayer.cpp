#include "BuyLayer.h"


namespace QUAT {


BuyLayer * BuyLayer::create(float sectionWidth,
                            float sectionHeight)
{
    BuyLayer *pRet = new(std::nothrow) BuyLayer(sectionWidth, sectionHeight);
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

void BuyLayer::updateFromModel(Game * game) {
}

void BuyLayer::buyCallback() {
}

bool BuyLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }
  
  // Store the radius and the width
  float padding      = sectionWidth * 0.05,
        borderRadius = sectionWidth * 0.05,
        borderWidth  = sectionWidth *  0.008,
        buttonWidth  = sectionWidth * 0.2,
        buttonIconHeight = sectionHeight * 0.2,
        cardWidth    = sectionWidth - buttonWidth - padding;

  this->buyButton = FAMenuButton::create(u"\uf0d6",
                                          buttonIconHeight,
                                          buttonWidth,
                                          sectionHeight,
                                          borderRadius,
                                          borderWidth);
  this->addChild(this->buyButton);

  this->buyButton->upCallback = CC_CALLBACK_0(BuyLayer::buyCallback, this);

  this->border = RectRadius::create(cardWidth, 
                                    sectionHeight, 
                                    borderRadius, 
                                    borderWidth, 
                                    false);
  this->border->setPositionX(buttonWidth + padding + (cardWidth / 2));
  this->border->setPositionY(sectionHeight / 2);
  this->border->setColor(cocos2d::Color4B::WHITE);
  this->addChild(this->border, 1);

  float fontSize = sectionHeight * 0.15;
  this->pleaLabel = Label::createWithTTF("Development of QUAT is supported by ads. Help us stay alive by paying a dollar to remove them.", 
                                         Q_FONT_PATH, 
                                         fontSize);
  this->pleaLabel->setHorizontalAlignment(TextHAlignment::CENTER);
  this->pleaLabel->setVerticalAlignment(TextVAlignment::CENTER);
  this->pleaLabel->setDimensions(cardWidth * 0.8, sectionHeight);
  this->pleaLabel->setPosition(buttonWidth + padding + (cardWidth / 2),
                               sectionHeight / 2);
  this->addChild(pleaLabel);

  this->setContentSize(cocos2d::Size(sectionWidth,
                                     sectionHeight));

  // Indicates we initialized successfully
  return true;
}

BuyLayer::BuyLayer(float sectionWidth,
                   float sectionHeight) {
  this->sectionWidth = sectionWidth;
  this->sectionHeight = sectionHeight;
}



}

