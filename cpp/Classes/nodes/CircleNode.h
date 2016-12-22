#ifndef __CIRCLE_NODE_H__
#define __CIRCLE_NODE_H__

#include "cocos2d.h"

#define CIRCLE_POINT_COUNT 200

namespace QUAT {

class CircleNode : public cocos2d::Layer
{
private:
  float radius,
        angle;

  int points;

	/**
	 * Redraws the rectangle from stored vertices.
	 */
	void drawCircle();

	void generateVertices();

	cocos2d::Vec2 vertices[CIRCLE_POINT_COUNT + 2];

	cocos2d::DrawNode * node;

	cocos2d::Color4F drawColor;
public:
	/**
	 * Creates and returns a CircleNode.
	 * @param  width        The width of the CircleNode.
	 * @param  height       The height of the CircleNode.
	 * @param  borderRadius The corner border radius.
	 * @param  borderWidth  The border thickness.
	 * @param  filled       Whether or not the rect is filled.
	 */
	static CircleNode * create(float radius);
	
	bool init();
	
	CircleNode(float radius);

  void setPercent(float percent);

	/**
	 * Sets the draw color of the rect and redraws.
	 * @param color The new color.
	 */
	void setColor(const cocos2d::Color4B &color);

	/**
	 * Sets the opacity of the rect.
	 * @param opacity [description]
	 */
	void setOpacity(GLubyte opacity);
};

}

#endif // __CIRCLE_NODE_H__
