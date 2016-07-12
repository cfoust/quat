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
          wordSize = fontSize,
    	  gap = wordSize * 1.8,
    	  panelHeight = fontSize + (width * .09);
    
    this->goalWord = WordNode::create(wordSize, gap);
    goalWord->changeWord(new std::string("GOAL"));
    goalWord->setPosition(gameBounds->origin.x + (width / 2), 
                          height * 0.55);
    this->addChild(goalWord);
    
	this->currentWord = BorderedWordNode::create(wordSize, gap);
    currentWord->changeWord(new std::string("WORD"));
    currentWord->setPosition(gameBounds->origin.x + (width / 2), 
                             goalWord->getPositionY() + wordSize * 1.6);
    currentWord->recalculateBounds();
    this->addChild(currentWord);

    this->undo = cocos2d::Sprite::create("undo.png");
    undo->setPosition(gameBounds->origin.x + width * 0.07,
                     currentWord->getPositionY());

    float scale = (fontSize * 0.8)/ undo->getBoundingBox().size.height;
    undo->setScale(scale,scale);
    auto box = undo->getBoundingBox();
    this->addChild(undo);

    return true;
}

SolutionLayer::SolutionLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}

}