#include "CreditsLayer.h"


namespace QUAT {


CreditsLayer * CreditsLayer::create(float width, float height)
{
    CreditsLayer *pRet = new(std::nothrow) CreditsLayer(width, height);
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


bool CreditsLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  float fontSize = height * 0.15;
  auto headerLabel = Label::createWithTTF("", Q_FONT_PATH, fontSize);

  headerLabel->setString("QUAT was crafted with love by Caleb Foust (@calebfoust) and David Seitz (@davidsights). This one is for those golden afternoons in St. Germaine.");

  headerLabel->setHorizontalAlignment(TextHAlignment::CENTER);
  headerLabel->setOpacity(120);
  headerLabel->setDimensions(width, height);
  headerLabel->setPositionX(width / 2);
  headerLabel->setPositionY(height / 2);
  this->addChild(headerLabel);

  this->setContentSize(cocos2d::Size(width, height));

  return true;
}

CreditsLayer::CreditsLayer(float width, float height) {
  this->width = width;
  this->height = height;
}



}

