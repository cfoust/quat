#include "CircleNode.h"

#include <cmath>
#define PI 3.14159265

namespace QUAT {

CircleNode * CircleNode::create(float radius) {
	CircleNode *pRet = new(std::nothrow) CircleNode(radius);

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

void CircleNode::drawCircle() {
	this->node->clear();
	this->node->drawPolygon(vertices, 
                          this->points, 
                          this->drawColor, 
                          1,
                          this->drawColor);
}
	
void CircleNode::generateVertices() {
  // Set up the variables for generating a quarter of a circle
  float step   = (2 * PI) / CIRCLE_POINT_COUNT;

  int index = 0;

  // Initialize at origin
  vertices[index].set(0, 0);
  index++;

  // Generate the rest of the points
  float pAngle; // The angle for the current point
  for (int i = 0; i < CIRCLE_POINT_COUNT; i++, index++) {
    // Start at the top of the circle
    pAngle = (i * step) + (PI / 2);

    // This means we passed the point we were supposed to
    if ((pAngle - (PI / 2)) > angle) {
      vertices[index].set(radius * cos(angle + (PI / 2)), 
          radius * sin(angle + (PI / 2)));
      break;
    // Otherwise generate the point as needed
    } else {
      vertices[index].set(radius * cos(pAngle), 
          radius * sin(pAngle));
    }
  }

  // Return to origin
  vertices[index++].set(0, 0);

  this->points = index++;
}
bool CircleNode::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  this->drawColor = cocos2d::Color4F::WHITE;
  this->angle = PI * 2;

  // Create the node
  this->node = cocos2d::DrawNode::create();
  this->addChild(this->node);

  this->generateVertices();
  this->drawCircle();

  return true;
}

CircleNode::CircleNode(float radius) {
  this->radius = radius;
}

void CircleNode::setPercent(float percent) {
  this->angle = percent * 2 * PI;
  this->generateVertices();
	this->drawCircle();
}

void CircleNode::setColor(const cocos2d::Color4B &color) {
	Layer::setColor(cocos2d::Color3B(color));
	this->drawColor = cocos2d::Color4F(color);
	this->drawCircle();
}

void CircleNode::setOpacity(GLubyte opacity) {
  cocos2d::Layer::setOpacity(opacity);
  auto color = cocos2d::Color4B(this->drawColor);
  color.a = opacity;
  this->setColor(color);
}

}
