#ifndef __KEYBOARD_LAYER_H__
#define __KEYBOARD_LAYER_H__

#include "cocos2d.h"

#include "WordNode.h"
#include "BorderedWordNode.h"

namespace QUAT {

class KeyboardLayer : public cocos2d::Layer
{
private:
	// Bounds of the game that we render in
	cocos2d::Rect * gameBounds;

	float fontSize;

public:
	/**
	 * Initialize the solution layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();
	
	KeyboardLayer(cocos2d::Rect * gameBounds, float fontSize);

	void none();
	
	static KeyboardLayer * create(cocos2d::Rect * gameBounds, float fontSize);
};

}

#endif // __KEYBOARD_LAYER_H__
