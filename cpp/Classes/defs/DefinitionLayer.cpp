#include "DefinitionLayer.h"


namespace QUAT {

void DefinitionLayer::updateWords(std::string current, std::string goal) {

}


DefinitionLayer * DefinitionLayer::create(cocos2d::Rect * gameBounds, float fontSize, Game * model)
{
    DefinitionLayer *pRet = new(std::nothrow) DefinitionLayer(gameBounds, fontSize, model);
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

    float definitionsWidth = width * 0.7;

    // Initialize both definitions that make it easy to display them
    this->currentDef = Definition::create(fontSize, definitionsWidth);
    this->currentDef->setPosition(gameBounds->origin.x + (width / 2),
                              height / 2);
    this->addChild(this->currentDef);

    this->goalDef = Definition::create(fontSize, definitionsWidth);
    this->goalDef->setPosition(gameBounds->origin.x + (width / 2),
                              height / 2);
    this->addChild(this->goalDef);


    // Initialize the subtitles (the current word and goal word subtitle text)
    float subtitleSize = this->fontSize * 0.4;
    this->currentTitle = cocos2d::Label::createWithTTF("current word", Q_FONT_PATH, subtitleSize);
    this->currentTitle->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
    this->currentTitle->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
    this->currentTitle->setPosition(gameBounds->origin.x + (width / 2)
                                    - definitionsWidth / 2, 
                                height * 0.75);
    this->addChild(this->currentTitle);

    this->goalTitle = cocos2d::Label::createWithTTF("goal word", Q_FONT_PATH, subtitleSize);
    this->goalTitle->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
    this->goalTitle->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
    this->goalTitle->setPosition(gameBounds->origin.x + (width / 2)
                                - definitionsWidth / 2, 
                                height * 0.62);
    this->addChild(this->goalTitle);

    // Make everything look pretty
    this->currentDef->setPositionY(this->currentTitle->getPositionY() - subtitleSize);
    this->goalTitle->setPositionY(this->currentDef->getPositionY()
                                  - this->currentDef->getTotalHeight()
                                   - subtitleSize);
    this->goalDef->setPositionY(this->goalTitle->getPositionY() - subtitleSize);

    // Indicates we initialized successfully
    return true;
}

DefinitionLayer::DefinitionLayer(cocos2d::Rect * gameBounds, float fontSize, Game * model) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
    this->dict = model->getDictionary();
}



}