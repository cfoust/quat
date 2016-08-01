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

    float size       = this->fontSize * Q_CURRENT_PADDING,
    	  radius     = this->fontSize * Q_CURRENT_BORDER_RADIUS,
    	  width      = this->fontSize * Q_CURRENT_BORDER_WIDTH;

    this->difference = size - (*this->bounds)[0]->size.width;

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
	this->fills[3 - column]->setColor(*this->selectedColor);
}

void BorderedWordNode::unselect() {
	for (int i = 0; i < 4; i++) {
		auto fill = this->fills[i];
    	fill->setColor(*this->defaultColor);
    }
}

void BorderedWordNode::recalculateBounds() {
    // Initialize all the pretty calculations
    float x = this->getPositionX(),
          y = this->getPositionY(),
          fontHeight = this->fontSize,
          fontHeightHalf = fontHeight / 2,
          fontWidth = fontHeight * 0.8,
          fontWidthHalf = fontWidth / 2,
          delta = this->difference / 2;

    // Calculate bound rectangles for all of the letters
    for (int i = 0; i < 4; i++) {
        auto letter = (*this->letterPool)[i];
        auto rect = (*this->bounds)[i];

        rect->setRect(x - letter->getPositionX() - fontWidthHalf - delta,
                      y - fontHeightHalf - delta,
                      fontWidth + difference,
                      fontHeight + difference);
    }

    auto first = (*this->bounds)[0],
         last  = (*this->bounds)[3];

    whole->setRect(first->origin.x - delta,
                   first->origin.y - delta,
                   ((last->origin.x + last->size.width) - first->origin.x + difference),
                   first->size.height + difference);
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