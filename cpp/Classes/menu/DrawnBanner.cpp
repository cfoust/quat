
#include "DrawnBanner.h"

#include <cmath>
#define PI 3.14159265

namespace QUAT {

DrawnBanner * DrawnBanner::create(float width, float height, cocos2d::Color4B * fillColor) {
	DrawnBanner *pRet = new(std::nothrow) DrawnBanner(width, height, fillColor);

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

void DrawnBanner::drawBanner() {
	this->node->clear();
	this->node->drawPolygon(vertices,
						    3,
                *this->fillColor,
						    0,
						    *this->fillColor);
	this->node->drawPolygon(vertices + 2,
						    4,
                *this->fillColor,
						    0,
						    *this->fillColor);
}

void DrawnBanner::update(int rank) {
  this->rankText->setString(std::to_string(rank));
}
void DrawnBanner::generateVertices() {
    float width = this->width,
          height = this->height;

    // Now we go up to the midpoint
    this->vertices[0].set(width / 2, height * 0.25);
  
    // Back to the bottom right corner
    this->vertices[1].set(width, 0.0);
   
    // Now to the top right
    this->vertices[2].set(width, height);
    
    // Now the top left
    this->vertices[3].set(0, height);
    
    // Generates the first point at the origin
    this->vertices[4].set(0.0, 0.0);
   
    // Now we go up to the midpoint
    this->vertices[5].set(width / 2, height * 0.25);
}
bool DrawnBanner::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }

    // Create the node
    this->node = cocos2d::DrawNode::create();
    this->addChild(this->node);

    float fontSize = 0.5 * this->height;
    this->rankText = cocos2d::Label::createWithTTF("1", Q_FONT_PATH, fontSize);
    this->rankText->setPositionX(this->width / 2);
    this->rankText->setPositionY(this->height * 0.6);
    this->addChild(this->rankText, 2);

    this->generateVertices();
    this->drawBanner();

    return true;
}

void DrawnBanner::setWidth(float width) {
  this->width = width;
  this->generateVertices();
  this->drawBanner();
}
void DrawnBanner::setHeight(float height) {
  this->height = height;
  this->generateVertices();
  this->drawBanner();
}

DrawnBanner::DrawnBanner(float width, float height, cocos2d::Color4B * fillColor) {
	this->width = width;
	this->height = height;
	this->fillColor = new cocos2d::Color4F(*fillColor);
}
void DrawnBanner::setOpacity(GLubyte opacity) {
	this->node->setOpacity(opacity);
}

}