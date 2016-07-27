#ifndef __MENU_BUTTON_LAYER_H__
#define __MENU_BUTTON_LAYER_H__

#include "cocos2d.h"
#include "../Clickable.h"

namespace QUAT {

class MenuButtonLayer : public Clickable
{
private:
	cocos2d::Sprite * background;
	cocos2d::Label * textLabel;

	float _size;

	void up();
	void entered();
	void left();
public:
	bool init();
	
	MenuButtonLayer(float size);
	
	static MenuButtonLayer * create(float size);
};

}

#endif // __MENU_BUTTON_LAYER_H__
