#include "ExplodingCircle.h"

namespace QUAT {

void ExplodingCircle::drawCircle() {
	this->circle->clear();
	this->circle->drawSolidCircle( cocos2d::Vec2(0,0), 
								   40, // Radius
								   CC_DEGREES_TO_RADIANS(360), 
								   50, // Segments
								   cocos2d::Color4F(this->drawColor));
}

bool ExplodingCircle::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }
    this->drawColor = cocos2d::Color4B::WHITE;

    this->circle = cocos2d::DrawNode::create();
    this->addChild(this->circle);

    this->drawCircle();

    return true;
}

ExplodingCircle::ExplodingCircle() {
}

void ExplodingCircle::setScale(float scale) {
	this->circle->setScale(scale);
}

void ExplodingCircle::setScaleX(float scaleX) {
	this->circle->setScaleX(scaleX);
}
void ExplodingCircle::setScaleY(float scaleY) {
	this->circle->setScaleY(scaleY);
}
void ExplodingCircle::setScale(float X, float Y) {
	this->circle->setScale(X, Y);
}

void ExplodingCircle::setColor(const cocos2d::Color4B &color) {
	this->drawColor = color;
	this->drawCircle();
}

void ExplodingCircle::setOpacity(GLubyte opacity) {
	this->drawColor.a = opacity;
	this->drawCircle();
}

ExplodingCircle * ExplodingCircle::create() {
	ExplodingCircle *pRet = new(std::nothrow) ExplodingCircle();

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