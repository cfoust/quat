#ifndef __MENU_BUTTON_LAYER_H__
#define __MENU_BUTTON_LAYER_H__

#include "cocos2d.h"
#include "../nodes/RectRadius.h"
#include "../Clickable.h"

namespace QUAT {

class MenuButtonLayer : public Clickable
{
private:
	RectRadius * circle;

	float _size;

	void up();
	void entered();
	void left();
	void recalculateBounds();
public:
	bool init();
	
	MenuButtonLayer(float size);
	
	static MenuButtonLayer * create(float size);
};

}

#endif // __MENU_BUTTON_LAYER_H__
