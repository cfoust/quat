#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "../models/Game.h"
#include "../GameStateController.h"

// For drawing the QUAT logo
#include "../solver/input/BorderedWordNode.h"

#include "EndlessLayer.h"
#include "TimedLayer.h"
#include "NavButtonLayer.h"

namespace QUAT {

USING_NS_CC;

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

	// Controls the entire game so we can move to other screens
	GameStateController * GSC;

  // Pointer to the game model so we can take input and manipulate it
  Game * game;

  // Enables scrolling when menu content is too long for one
  // screen to show
  ui::ScrollView * scrollView;

	// Yeah, this element is a "live" element -- not a sprite
	BorderedWordNode * quatLogo;

  // Displays information about the user's progress in endless
  // mode.
  EndlessLayer * endlessLayer;
  // The same, but for timed mode. Shows the high score.
  TimedLayer * timedLayer;

  // Repositions everything and activates scrolling if necesary
  void resetLayout();

public:

  // Three callbacks for the game modes
  void continueEndless();
  void continueTimed();
  void playTimed();
  void restartTimed();

	/**
	 * Initialize this layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

	MenuLayer(cocos2d::Rect * gameBounds, 
            float fontSize,
            Game * game,
            GameStateController * GSC);

  void updateFromModel(Game * game);

	/**
	 * Creates a MenuLayer object.
	 */
	static MenuLayer * create(cocos2d::Rect * gameBounds,
                            float fontSize,
                            Game * game,
                            GameStateController * GSC);
};

}

#endif // __MENU_LAYER_H__
