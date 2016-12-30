#include "TimedCard.h"

#include <string>

USING_NS_CC;

namespace QUAT {

TimedCard * TimedCard::create(float fontSize,
               float width,
               float height)
{
    TimedCard *pRet = new(std::nothrow) TimedCard(fontSize,
                                                    width,
                                                    height);
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

float TimedCard::getBorderRadius() {
  return this->borderRadius;
}

float TimedCard::getBorderWidth() {
  return this->borderWidth;
}
bool TimedCard::init() {
	// Init the super class
    if ( !cocos2d::Layer::init() )
    {
        return false;
    }


    // Store the radius and the width
    borderRadius = this->_width * 0.05;
    borderWidth = this->_width *  0.008;

    // Set the default color
    this->defaultColor = new cocos2d::Color4B(255,255,255,64);
    this->fillInColor = new cocos2d::Color4B(255,255,255,120);

    // Creates the white border around the edges
    this->border = RectRadius::create(this->_width, this->_height, borderRadius, borderWidth, false);
    this->border->setPositionX(this->_width / 2);
    this->border->setPositionY(this->_height / 2);
    this->border->setColor(cocos2d::Color4B::WHITE);
    this->addChild(this->border, 1);

    this->setContentSize(cocos2d::Size(this->_width, this->_height));

    return true;
}

TimedCard::TimedCard(float fontSize,
               float width,
               float height)
{
  	this->fontSize = fontSize;
    this->_width = width;
    this->_height = height;
}


};
