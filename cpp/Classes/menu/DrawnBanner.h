
#ifndef __DRAWN_BANNER_H__
#define __DRAWN_BANNER_H__

#include "cocos2d.h"
#include "../Constants.h"

namespace QUAT {

class DrawnBanner : public cocos2d::Layer
{
private:
	float width, // Width of the rect
		    height, // Height of the rect
        fontSize;

	/**
	 * Redraws the rectangle from stored vertices.
	 */
	void drawBanner();

	void generateVertices();

	cocos2d::Vec2 vertices[6];

	cocos2d::DrawNode * node;

	cocos2d::Label * rankText;

	cocos2d::Color4F * fillColor;

public:
	static DrawnBanner * create(float width, float height);

  // Two creation methods, one for changing the font size
	static DrawnBanner * create(float width, float height, float fontSize);

	bool init();

	DrawnBanner(float width, float height, float fontSize);

  void update(int rank);

	void setWidth(float width);

	void setHeight(float height);

	/**
	 * Sets the opacity of the rect.
	 * @param opacity [description]
	 */
	void setOpacity(GLubyte opacity);
};

}

#endif // __DRAWN_BANNER_H__
