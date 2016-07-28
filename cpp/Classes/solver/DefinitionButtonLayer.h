#ifndef __DEFINITION_BUTTON_LAYER_H__
#define __DEFINITION_BUTTON_LAYER_H__

#include "cocos2d.h"
#include "../Clickable.h"

namespace QUAT {

class DefinitionButtonLayer : public Clickable
{
private:
	cocos2d::Sprite * background;

	float _height;

	void up();
	void entered();
	void left();
public:
	bool init();
	
	DefinitionButtonLayer(float height);
	
	static DefinitionButtonLayer * create(float height);

	void update(int newVal);
};

}

#endif // __DEFINITION_BUTTON_LAYER_H__
