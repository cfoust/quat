#include "DefinitionLayer.h"


namespace QUAT {


DefinitionLayer * DefinitionLayer::create(cocos2d::Rect * gameBounds, float fontSize)
{
    DefinitionLayer *pRet = new(std::nothrow) DefinitionLayer(gameBounds, fontSize);
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

bool DefinitionLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }

    // Calculates all of the necessary ratios
    float width = gameBounds->size.width,
          height = gameBounds->size.height,
          wordSize = fontSize,
          gap = wordSize * Q_LETTER_GAP;

    // Creates the QUAT logo that sits at the top of the screen
    float proportion = 0.6;
    this->quatLogo = BorderedWordNode::create(wordSize * proportion, gap * proportion);
    this->quatLogo->changeWord(new std::string("QUAT"));
    this->quatLogo->setPosition(gameBounds->origin.x + (width / 2), 
                                height * 0.9);
    this->addChild(this->quatLogo);

    // Creates the "Definitions" title
    float titleSize = this->fontSize * 0.72;
    this->title = cocos2d::Label::createWithTTF("Definitions", Q_FONT_PATH, titleSize);
    this->title->setPosition(gameBounds->origin.x + (width / 2), 
                                height * 0.82);
    this->addChild(this->title);

    // Creates the "sponsored by dictionary" subtitle
    // Kind of pointless right now, but we're doing it to match the wireframe
    this->sponsor = cocos2d::Label::createWithTTF("sponsored by dictionary", Q_FONT_PATH, titleSize * 0.5);
    this->sponsor->setOpacity(150);
    this->sponsor->setPosition(gameBounds->origin.x + (width / 2), 
                               this->title->getPositionY() - titleSize * 0.8);
    this->addChild(this->sponsor);
    
    // Indicates we initialized successfully
    return true;
}

DefinitionLayer::DefinitionLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}



}