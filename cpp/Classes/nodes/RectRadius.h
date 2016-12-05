#ifndef __RECT_RADIUS_H__
#define __RECT_RADIUS_H__

#include "cocos2d.h"

#define RECT_POINT_COUNT 30

namespace QUAT {

class RectRadius : public cocos2d::Layer
{
private:
	float width, // Width of the rect
		  height, // Height of the rect
		  borderRadius, // Border radius of the rect
		  borderWidth; // Border thickness

	bool filled; // Whether or not the radius is filled

	/**
	 * Redraws the rectangle from stored vertices.
	 */
	void drawRect();

	void generateVertices();

	cocos2d::Vec2 vertices[RECT_POINT_COUNT * 4];

	cocos2d::DrawNode * node;

	cocos2d::Color4F drawColor;
public:
	/**
	 * Creates and returns a RectRadius.
	 * @param  width        The width of the RectRadius.
	 * @param  height       The height of the RectRadius.
	 * @param  borderRadius The corner border radius.
	 * @param  borderWidth  The border thickness.
	 * @param  filled       Whether or not the rect is filled.
	 */
	static RectRadius * create(float width, float height, float borderRadius, float borderWidth, bool filled);
	
	bool init();
	
	RectRadius(float width, float height, float borderRadius, float borderWidth, bool filled);

	/**
	 * Sets the draw color of the rect and redraws.
	 * @param color The new color.
	 */
	void setColor(const cocos2d::Color4B &color);

	void setWidth(float width);

	void setHeight(float height);

	/**
	 * Sets the opacity of the rect.
	 * @param opacity [description]
	 */
	void setOpacity(GLubyte opacity);
};

}

#endif // __RECT_RADIUS_H__
