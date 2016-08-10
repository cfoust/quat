#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"
#include "../solver/input/BorderedWordNode.h"


namespace QUAT {

class MenuLayer : public cocos2d::Layer
{
private:
	// Stores the font size given to us by the global context. Most graphical
	// calculations are based on this so that you could adjust it if you wanted
	// to.
	float fontSize;

	// Contains the bounds of the game (just the portrait part) handed down
	// by the global context. All user interface elements in MenuLayer are
	// built inside these bounds.
	cocos2d::Rect * gameBounds;

	// Yeah, this element is a "live" element -- not a sprite
	BorderedWordNode * quatLogo;


public:
	/**
	 * Initialize this layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();
	
	MenuLayer(cocos2d::Rect * gameBounds, float fontSize);
	
	/**
	 * Creates a MenuLayer object.
	 */
	static MenuLayer * create(cocos2d::Rect * gameBounds, float fontSize);
};

}

#endif // __MENU_LAYER_H__