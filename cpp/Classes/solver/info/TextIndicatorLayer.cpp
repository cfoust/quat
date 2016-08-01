#include "TextIndicatorLayer.h"


namespace QUAT {

void TextIndicatorLayer::display(std::string str) {
	this->setText(str);
	this->text->stopAllActions();
	this->text->setOpacity(0);
	auto fade = cocos2d::Sequence::create(cocos2d::FadeTo::create(Q_TEXT_INDICATOR_FADE, 255),
								   cocos2d::DelayTime::create(Q_TEXT_INDICATOR_FADE),
								   cocos2d::FadeTo::create(Q_TEXT_INDICATOR_FADE, 0),
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

    this->text = cocos2d::Label::createWithTTF("Done!", Q_FONT_PATH, this->fontSize);
    this->text->setOpacity(0);
    this->addChild(this->text);

	return true;
}


TextIndicatorLayer::TextIndicatorLayer(float fontSize) {
    this->fontSize = fontSize * Q_TEXT_INDICATOR_FONT;
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