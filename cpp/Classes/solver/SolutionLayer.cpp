#include "SolutionLayer.h"
#include "WordNode.h"

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
    
    auto ttf0 = WordNode::create(80, 50);
    
    ttf0->setPosition(Vec2(width / 2, height / 2));
    ttf0->changeWord(new std::string("PORN"));
    this->addChild(ttf0);
    
	
    return true;
}

SolutionLayer::SolutionLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}

}