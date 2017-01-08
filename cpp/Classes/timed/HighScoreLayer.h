#ifndef __HIGH_SCORE_LAYER_H__
#define __HIGH_SCORE_LAYER_H__

#include "cocos2d.h"
#include "../menu/IconMenuButton.h"
#include "../menu/DrawnBanner.h"
#include "../Constants.h"
#include "../models/Game.h"
#include "../models/TimeUtils.h"
#include "../GameStateController.h"

USING_NS_CC;
namespace QUAT {

class HighScoreLayer : public cocos2d::Layer
{
private:
  // The bounds of the game client
  cocos2d::Rect * gameBounds;

  // The text that sits in the middle of the circle
	cocos2d::Label * scoreText;

	// Controls the entire game so we can move to other screens
	GameStateController * GSC;

  // Banner representing the goal rank
  DrawnBanner * banner;

  // Game state
  Game * game;

public:
  void restartCallback();

  IconMenuButton * restartButton;

	virtual bool init();

	HighScoreLayer(Game * game,
                 cocos2d::Rect * gameBounds,
                 GameStateController * GSC);

  void updateFromModel();

	static HighScoreLayer * create(Game * game,
                                 cocos2d::Rect * gameBounds,
                                 GameStateController * GSC);
};

}

#endif // __HIGH_SCORE_LAYER_H__
