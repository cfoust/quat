#include "TextIndicatorLayer.h"


namespace QUAT {

void TextIndicatorLayer::display(std::string str) {
	this->setText(str);
	this->text->stopAllActions();
	this->text->setOpacity(0);
	auto fade = cocos2d::Sequence::create(cocos2d::FadeTo::create(0.75, 255),
								   cocos2d::DelayTime::create(0.75),
								   cocos2d::FadeTo::create(0.75, 0),
								   nullptr);

	this->text->runAction(fade);
}

void TextIndicatorLayer::setText(std::string str) {
	this->text->setString(str);
}

bool TextIndicatorLayer::init() {
	// Init the super class
    if ( !cocos2d::Layer::init() )
    {
        return false;
    }

    this->text = cocos2d::Label::createWithTTF("Done!", "fonts/Arimo-Regular.ttf", this->fontSize);
    this->addChild(this->text);

	return true;
}


TextIndicatorLayer::TextIndicatorLayer(float fontSize) {
    this->fontSize = fontSize * 0.40;
}


TextIndicatorLayer * TextIndicatorLayer::create(float fontSize)
{
    TextIndicatorLayer *pRet = new(std::nothrow) TextIndicatorLayer(fontSize);
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