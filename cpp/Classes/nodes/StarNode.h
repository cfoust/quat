#ifndef __STAR_NODE_H__
#define __STAR_NODE_H__

#include "cocos2d.h"

namespace QUAT {

class StarNode : public cocos2d::Layer
{
private:
  float size;

	void drawStar();

	void generateVertices();

	cocos2d::Vec2 vertices[];

	cocos2d::DrawNode * node;

	cocos2d::Color4F drawColor;
public:
	/**
	 * Creates and returns a StarNode.
	 */
	static StarNode * create(float size);
	
	bool init();
	
	StarNode(float size);

  cocos2d::DrawNode * getNode();

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

#endif // __STAR_NODE_H__
