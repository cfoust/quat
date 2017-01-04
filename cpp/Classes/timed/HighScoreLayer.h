#ifndef __HIGH_SCORE_LAYER_H__
#define __HIGH_SCORE_LAYER_H__

#include "cocos2d.h"
#include "../menu/MenuButton.h"
#include "../Constants.h"
#include "../models/Game.h"
#include "../models/TimeUtils.h"
#include "../GameStateController.h"

USING_NS_CC;
namespace QUAT {

#define TRANS_SECS 3

class HighScoreLayer : public cocos2d::Layer
{
private:
  // The bounds of the game client
  cocos2d::Rect * gameBounds;

  // The text that sits in the middle of the circle
	cocos2d::Label * scoreText;

	// Controls the entire game so we can move to other screens
	GameStateController * GSC;
public:
  MenuButton * restartButton;

	virtual bool init();

	HighScoreLayer(cocos2d::Rect * gameBounds,
                 GameStateController * GSC);

  void updateFromModel(Game * game);

	static HighScoreLayer * create(cocos2d::Rect * gameBounds,
                                 GameStateController * GSC);
};

}

#endif // __HIGH_SCORE_LAYER_H__
