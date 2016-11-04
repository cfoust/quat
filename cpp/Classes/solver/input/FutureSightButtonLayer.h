#ifndef __FUTURE_SIGHT_BUTTON_LAYER_H__
#define __FUTURE_SIGHT_BUTTON_LAYER_H__

#include "cocos2d.h"
#include "../../Clickable.h"

namespace QUAT {

class FutureSightButtonLayer : public Clickable
{
private:
	cocos2d::Sprite * background;

	float _height;

	void up();
	void entered();
	void left();
public:
	bool init();
	
	FutureSightButtonLayer(float height);
	
	static FutureSightButtonLayer * create(float height);

	void update(int newVal);
};

}

#endif // __FUTURE_SIGHT_BUTTON_LAYER_H__
