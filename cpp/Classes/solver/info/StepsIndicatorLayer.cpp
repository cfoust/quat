#include "StepsIndicatorLayer.h"

namespace QUAT {

void StepsIndicatorLayer::setOverPar(bool overPar) {
    this->overText->setVisible(overPar);
}
void StepsIndicatorLayer::update(int num) {
    this->stepText->setString(std::to_string(num));
}

bool StepsIndicatorLayer::init() {
	// Init the super class
    if ( !cocos2d::Layer::init() )
    {
        return false;
    }


    // Creates the main text
    float stepTextSize = this->fontSize * 0.4;
    this->stepText = cocos2d::Label::createWithTTF("5", Q_FONT_PATH, stepTextSize);
    this->stepText->setPositionX(stepTextSize * .12);
    this->addChild(this->stepText, 2);
  
    float circleSize = stepTextSize * 2,
          circleRadius = circleSize / 2,
          circlBorderWidth = circleRadius * 0.1;
    this->circle = RectRadius::create(circleSize, circleSize, circleRadius, circlBorderWidth, false);
    this->circle->setPositionX(circleSize * .1);
    this->addChild(this->circle, 0);

    this->overText = cocos2d::Label::createWithTTF("This puzzle can be solved in fewer steps.", Q_FONT_PATH, stepTextSize * 0.8);
    this->overText->setPositionX(0);
    this->overText->setPositionY(this->stepText->getPositionY() + (stepTextSize * 2));
    this->overText->setColor(cocos2d::Color3B(255,255,255));
    this->overText->setOpacity(180);
    this->overText->setVisible(false);
    this->addChild(this->overText, 2);

	return true;
}


StepsIndicatorLayer::StepsIndicatorLayer(float fontSize) {
    this->fontSize = fontSize;
}


StepsIndicatorLayer * StepsIndicatorLayer::create(float fontSize)
{
    StepsIndicatorLayer *pRet = new(std::nothrow) StepsIndicatorLayer(fontSize);
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


}
