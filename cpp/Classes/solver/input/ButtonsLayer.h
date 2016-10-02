#ifndef __BUTTONS_LAYER_H__
#define __BUTTONS_LAYER_H__

#include "cocos2d.h"
#include "BorderedWordNode.h"
#include "../../models/Game.h"
#include "../info/StepsIndicatorLayer.h"

namespace QUAT {

class ButtonsLayer : public cocos2d::Layer
{
private:
	// Stores the font size given to us by the global context. Most graphical
	// calculations are based on this so that you could adjust it if you wanted
	// to.
	float fontSize;


  // Contains the bounds of the game (just the portrait part) handed down
	// by the global context. All user interface elements in ButtonsLayer are
	// built inside these bounds.
	cocos2d::Rect * gameBounds;


	// Shows the number of steps the user has already played.
	StepsIndicatorLayer * stepsIndicatorLayer;
public:
	/**
	 * Initialize this layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();
	
	ButtonsLayer(cocos2d::Rect * gameBounds, float fontSize);
  
  void updateFromModel(Game * game);

	/**
	 * Creates a ButtonsLayer object.
	 */
	static ButtonsLayer * create(cocos2d::Rect * gameBounds, float fontSize);
};

}

#endif // __BUTTONS_LAYER_H__
