#ifndef __SKIP_BUTTON_LAYER_H__
#define __SKIP_BUTTON_LAYER_H__

#include "cocos2d.h"
#include "../../Clickable.h"

namespace QUAT {

class SkipButtonLayer : public Clickable
{
private:
	cocos2d::Sprite * background;
	cocos2d::DrawNode * line;

	float _height;

	void up();
	void entered();
	void left();
public:
	bool init();
	
	SkipButtonLayer(float height);
	
	static SkipButtonLayer * create(float height);

	void update(int newVal);
};

}

#endif // __SKIP_BUTTON_LAYER_H__
