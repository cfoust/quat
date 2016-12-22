#include "BlitzIndicatorLayer.h"

namespace QUAT {

void BlitzIndicatorLayer::updateFromModel(Game * game) {
  auto blitz = game->getUser()->getBlitz();
  this->multiplierText->setString(std::to_string(blitz->getMultiplier()) +
                                  std::string("x"));
  this->percent = blitz->percentRemaining();
  this->circle->setPercent(this->percent);
}


bool BlitzIndicatorLayer::init() {
	// Init the super class
  if ( !cocos2d::Layer::init() )
  {
      return false;
  }


  // Set the default color
  this->defaultColor = new cocos2d::Color4B(255,255,255,64);
  this->fillInColor = new cocos2d::Color4B(255,255,255,120);

  this->percent = 1;

  this->multiplierText = cocos2d::Label::createWithTTF("1X", Q_FONT_PATH, fontSize);
  this->addChild(this->multiplierText, 2);

  this->circle = CircleNode::create(50);
  this->addChild(this->circle);

	return true;
}


BlitzIndicatorLayer::BlitzIndicatorLayer(float fontSize, float barWidth) {
    this->fontSize = fontSize;
}


BlitzIndicatorLayer * BlitzIndicatorLayer::create(float fontSize, float barWidth)
{
    BlitzIndicatorLayer *pRet = new(std::nothrow) BlitzIndicatorLayer(fontSize, barWidth);
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
  this->multiplierText->setOpacity(opacity);
}

}
