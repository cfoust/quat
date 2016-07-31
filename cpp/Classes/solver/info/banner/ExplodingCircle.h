#ifndef __EXPLODING_CIRCLE_H__
#define __EXPLODING_CIRCLE_H__

#include "cocos2d.h"

namespace QUAT {

class ExplodingCircle : public cocos2d::Layer
{
private:
	cocos2d::DrawNode * circle;
	cocos2d::Color4B drawColor;
public:

	void drawCircle();

	virtual bool init();

	void setScale(float scale);
	void setScaleX(float scaleX);
	void setScaleY(float scaleY);
	void setScale(float X, float Y);

	void setColor(const cocos2d::Color4B &color);

	void setOpacity(GLubyte opacity);
	
	ExplodingCircle();
	
	static ExplodingCircle * create();
};

}

#endif // __EXPLODING_CIRCLE_H__
