#include "BorderedWordNode.h"

namespace QUAT {

bool BorderedWordNode::init() {
	// Init the super class
    if ( !WordNode::init() )
    {
        return false;
    }

    this->defaultColor = new cocos2d::Color4B(255,255,255,64);
    this->selectedColor = new cocos2d::Color4B(255,255,255,153);

    float size   = this->fontSize * 1.25,
    	  radius = this->fontSize * 0.24,
    	  width  = this->fontSize * 0.06;

    for (int i = 0; i < 4; i++) {
    	// Initialize the new RectRadius
    	this->borders[i] = RectRadius::create(size, size, radius, width, false);
    	auto border = this->borders[i];

    	// Grab the calculated bounds of the letter
    	auto bound = (*this->bounds)[i];

    	border->setPositionX(bound->origin.x + (bound->size.width / 2));
    	border->setPositionY(bound->origin.y + (bound->size.height / 2));

    	border->setColor(cocos2d::Color4B::WHITE);

    	this->addChild(border);

    	// Initialize the new RectRadius
    	this->fills[i] = RectRadius::create(size, size, radius, width, true);
    	auto fill = this->fills[i];

    	fill->setPositionX(bound->origin.x + (bound->size.width / 2));
    	fill->setPositionY(bound->origin.y + (bound->size.height / 2));

    	fill->setColor(*this->defaultColor);

    	this->addChild(fill);
    }

	return true;
}

void BorderedWordNode::select(int column) {
	this->fills[column]->setColor(*this->selectedColor);
}

void BorderedWordNode::unselect() {
	for (int i = 0; i < 4; i++) {
		auto fill = this->fills[i];
    	fill->setColor(*this->defaultColor);
    }
}

BorderedWordNode::BorderedWordNode(float fontSize, float fontGap) : WordNode(fontSize, fontGap) {
	
}

BorderedWordNode * BorderedWordNode::create(float fontSize, float fontGap)
{
    BorderedWordNode *pRet = new(std::nothrow) BorderedWordNode(fontSize, fontGap);
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