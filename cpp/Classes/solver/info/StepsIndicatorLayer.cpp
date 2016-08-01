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

    // Creates the subtext (which always just says "steps")
    float subtextSize = fontSize * Q_STEPTEXT_SUB_FONT; // The smaller font size
    this->subtext = cocos2d::Label::createWithTTF("steps", Q_FONT_PATH, subtextSize);
    this->subtext->setPositionX(0);
    this->subtext->setPositionY(subtextSize / 2);
    this->addChild(this->subtext, 2);

    // Creates the main text
    float stepTextSize = subtextSize * Q_STEPTEXT_STEP_FONT;
    this->stepText = cocos2d::Label::createWithTTF("5", Q_FONT_PATH, stepTextSize);
    this->stepText->setPositionX(0);
    this->stepText->setPositionY(this->subtext->getPositionY() + (stepTextSize * 0.9));
    this->addChild(this->stepText, 2);

    this->overText = cocos2d::Label::createWithTTF("This puzzle can be solved in fewer steps.", Q_FONT_PATH, subtextSize);
    this->overText->setPositionX(0);
    this->overText->setPositionY(this->stepText->getPositionY() + (stepTextSize));
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