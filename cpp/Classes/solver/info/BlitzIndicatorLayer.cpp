#include "BlitzIndicatorLayer.h"

namespace QUAT {

void BlitzIndicatorLayer::updateFromModel(Game * game) {
  auto blitz = game->getBlitzer();

  std::string multiplierText = std::to_string(blitz->getMultiplier()) +
                                  std::string("X");
  this->topText->setString(multiplierText);
  this->bottomText->setString(multiplierText);

  this->percent = blitz->percentRemaining();
  this->circle->setPercent(this->percent);
}

void BlitzIndicatorLayer::setScheme(ColorScheme scheme) {
}


bool BlitzIndicatorLayer::init() {
	// Init the super class
  if ( !cocos2d::Layer::init() )
  {
      return false;
  }


  // Default to full
  this->percent = 1;

  // The bottom and top text are used to clip and show the multiplier
  // as it animates down
  this->topText = cocos2d::Label::createWithTTF("1X", Q_FONT_PATH, fontSize);
  this->topText->setOpacity(40);
  this->topText->setColor(cocos2d::Color3B::WHITE);

  this->bottomText = cocos2d::Label::createWithTTF("1X", Q_FONT_PATH, fontSize);
  this->bottomText->setColor(cocos2d::Color3B::WHITE);
  this->bottomText->setOpacity(40);
  this->addChild(bottomText, 1);

  // The circle that animates the time remaining in the combo
  this->circle = CircleNode::create(50);
  this->circle->setColor(cocos2d::Color4B(255, 255, 255, 40));
  this->addChild(this->circle, 2);

  // Sets up the clipping for the main multiplier text
  auto clip = cocos2d::ClippingNode::create();
  clip->setStencil(this->circle->getNode());
  clip->setInverted(false);
  clip->addChild(this->topText);
  this->addChild(clip, 3);

	return true;
}


BlitzIndicatorLayer::BlitzIndicatorLayer(float fontSize) {
    this->fontSize = fontSize;
}


BlitzIndicatorLayer * BlitzIndicatorLayer::create(float fontSize)
{
    BlitzIndicatorLayer *pRet = new(std::nothrow) BlitzIndicatorLayer(fontSize);
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

void BlitzIndicatorLayer::setPercent(float p) {
  this->percent = p;
}
void BlitzIndicatorLayer::setOpacity(GLubyte opacity) {
  cocos2d::Layer::setOpacity(opacity);
  this->topText->setOpacity(opacity);
  this->bottomText->setOpacity(opacity);
}

}
