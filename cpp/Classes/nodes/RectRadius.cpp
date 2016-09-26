#include "RectRadius.h"

#include <cmath>
#define PI 3.14159265

namespace QUAT {

RectRadius * RectRadius::create(float width, float height, float borderRadius, float borderWidth, bool filled) {
	RectRadius *pRet = new(std::nothrow) RectRadius(width, height, borderRadius, borderWidth, filled);

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

void RectRadius::drawRect() {
	this->node->clear();
	this->node->drawPolygon(vertices, 
						    RECT_POINT_COUNT * 4, 
						    this->filled ? this->drawColor : cocos2d::Color4F(0,0,0,0),
						    this->borderWidth,
						    this->drawColor);
}
	
void RectRadius::generateVertices() {
    // Set up the variables for generating a quarter of a circle
    float step = (PI / 2) / RECT_POINT_COUNT,
    	  radius = this->borderRadius;

   	// Generate the curve
    cocos2d::Vec2 curve[RECT_POINT_COUNT];
    for (int i = 0; i < RECT_POINT_COUNT; i++) {
    	float angle = i * step;
    	curve[i] = cocos2d::Vec2(radius * cos(angle), radius * sin(angle));
    }

    float diffX = (this->width / 2) - this->borderRadius,
    	  diffY = (this->height / 2) - this->borderRadius;

    // Generate all the vertices we use for drawing
    for (int i = 0; i < 4; i++) {
        int dx = 1, 
            dy = 1,
            index = 0;
    	// Sets the way the curve is reflected
        dx *= ((i == 1) || (i == 2)) ? -1 : 1;
        dy *= ((i == 2) || (i == 3)) ? -1 : 1;

        // Iterate over the curve points
        for (int j = 0; j < RECT_POINT_COUNT; j++) {
            cocos2d::Vec2 p;

            // These if statements correct the orientation of the curve
            if ((i == 1) || (i == 3)) {
                p = cocos2d::Vec2(curve[(RECT_POINT_COUNT - 1) - j]);
            } else {
                p = cocos2d::Vec2(curve[j]);
            }

            p.x = (p.x + diffX) * dx;
            p.y = (p.y + diffY) * dy;
            
            index = (i * RECT_POINT_COUNT) + j; 

            this->vertices[index].set(p);
        }
    }
}
bool RectRadius::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }

    // Needed this to change the perceived border size
    this->borderWidth *= 0.6;

    // Handle bad inputs (if there isn't enough space for this radius)
    float doubleBorder = borderRadius * 2;
    if (doubleBorder > this->width) {
        this->borderRadius = this->width / 2;
    }
    if (doubleBorder > this->height) {
        this->borderRadius = this->height / 2;
    }

    // Create the node
    this->node = cocos2d::DrawNode::create();
    this->addChild(this->node);

    this->generateVertices();
    this->drawRect();

    return true;
}

void RectRadius::setWidth(float width) {
  this->width = width;
  this->generateVertices();
  this->drawRect();
}
void RectRadius::setHeight(float height) {
  this->height = height;
  this->generateVertices();
  this->drawRect();
}

RectRadius::RectRadius(float width, float height, float borderRadius, float borderWidth, bool filled) {
	this->width = width;
	this->height = height;
	this->borderRadius = borderRadius;
	this->borderWidth = borderWidth;
	this->filled = filled;
	this->drawColor = cocos2d::Color4F::WHITE;
}

void RectRadius::setColor(const cocos2d::Color4B &color) {
	Layer::setColor(cocos2d::Color3B(color));
	this->drawColor = cocos2d::Color4F(color);

	this->drawRect();
}

void RectRadius::setOpacity(GLubyte opacity) {
	this->node->setOpacity(opacity);
}

}
