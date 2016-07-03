#include "SolutionLayer.h"
#include "../menu/MenuButton.h"

#include <string>

USING_NS_CC;

namespace QUAT {

SolutionLayer * SolutionLayer::create(cocos2d::Rect * gameBounds, float fontSize)
{
    SolutionLayer *pRet = new(std::nothrow) SolutionLayer(gameBounds, fontSize);
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

void SolutionLayer::menu() {
    log("Test");
}


bool SolutionLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Calculates all of the necessary ratios
    float width = gameBounds->size.width,
    	  height = gameBounds->size.height,
    	  fourths = width / 4,
    	  gap = fontSize * 1.6,
    	  panelHeight = fontSize + (width * .09);
    
    this->goalWord = WordNode::create(fontSize, gap);
    goalWord->changeWord(new std::string("GOAL"));
    goalWord->setPosition(gameBounds->origin.x + (width / 2), 
                          height / 2);
    this->addChild(goalWord);
    
	this->currentWord = BorderedWordNode::create(fontSize, gap);
    currentWord->changeWord(new std::string("WORD"));
    currentWord->setPosition(gameBounds->origin.x + (width / 2), 
                             goalWord->getPositionY() + fontSize * 1.4);
    this->addChild(currentWord);

    return true;
}

SolutionLayer::SolutionLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}

}