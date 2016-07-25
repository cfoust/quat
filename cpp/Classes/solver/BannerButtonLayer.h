#ifndef __BANNER_BUTTON_LAYER_H__
#define __BANNER_BUTTON_LAYER_H__

#include "cocos2d.h"
#include "../Clickable.h"

namespace QUAT {

class BannerButtonLayer : public Clickable
{
private:
	cocos2d::Sprite * background;
	cocos2d::Label * textLabel;

	float _height;

	void up();
	void entered();
	void left();
public:
	bool init();
	
	BannerButtonLayer(float height);
	
	static BannerButtonLayer * create(float height);

	void update(int newVal);
};

}

#endif // __BANNER_BUTTON_LAYER_H__
