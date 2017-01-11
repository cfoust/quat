#ifndef __AD_LAYER_H__
#define __AD_LAYER_H__

#include "cocos2d.h"
#include "../CloseButton.h"
#include "../Constants.h"
#include "../solver/input/BorderedWordNode.h"
#include "../nodes/RectRadius.h"
#include "../menu/RankCard.h"
#include "../models/Game.h"
#include "../models/TimeUtils.h"

namespace QUAT {

class AdLayer : public cocos2d::Layer
{
private:
	// Stores the font size given to us by the global context. Most graphical
	// calculations are based on this so that you could adjust it if you wanted
	// to.
	float fontSize;

	// Contains the bounds of the game (just the portrait part) handed down
	// by the global context. All user interface elements in AdLayer are
	// built inside these bounds.
	cocos2d::Rect * gameBounds;

	CloseButton * closeButton;

	// Yeah, this element is a "live" element -- not a sprite
	BorderedWordNode * quatLogo;

	cocos2d::Label * skipText,
                 * timeText;
	 
	RectRadius * adPlaceholder; // Placeholder for the ad rectangle

	int secondsRemaining; // Counts the number of seconds remaining in the
	                      // counter

  RankCard * rankCard;
public:
	/**
	 * Initialize this layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();
	
	AdLayer(cocos2d::Rect * gameBounds, float fontSize, CloseButton * closeButton);

	void startTimer();

	void updateTime(float dt);
	
  void updateFromModel(Game * game);
	/**
	 * Creates a AdLayer object.
	 */
	static AdLayer * create(cocos2d::Rect * gameBounds, float fontSize, CloseButton * closeButton);
};

}

#endif // __AD_LAYER_H__
