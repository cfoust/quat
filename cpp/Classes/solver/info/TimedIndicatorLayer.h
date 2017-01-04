#ifndef __TIMED_INDICATOR_LAYER_H__
#define __TIMED_INDICATOR_LAYER_H__

#include "cocos2d.h"
#include "../../Constants.h"
#include "../../models/Game.h"
#include "../../models/TimeUtils.h"

#include <string>

namespace QUAT {

USING_NS_CC;

class TimedIndicatorLayer : public Layer
{
private:
	Label * timer;
  
  // Holds the dimensions of the game
  cocos2d::Rect * gameBounds;

	float fontSize;

public:

  void updateFromModel(Game * game);

	/**
	 * Initialize the solution layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

	TimedIndicatorLayer(cocos2d::Rect * gameBounds, float fontSize);

	static TimedIndicatorLayer * create(cocos2d::Rect * gameBounds, float fontSize);
};

}

#endif // __TIMED_INDICATOR_LAYER_H__
