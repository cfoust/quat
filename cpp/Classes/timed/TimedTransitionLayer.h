#ifndef __TIMED_TRANSITION_LAYER_H__
#define __TIMED_TRANSITION_LAYER_H__

#include "cocos2d.h"
#include "../Constants.h"
#include "../nodes/CircleNode.h"

USING_NS_CC;
namespace QUAT {

class TimedTransitionLayer : public cocos2d::Layer
{
private:
  // The bounds of the game client
  cocos2d::Rect * gameBounds;

  // Animates a countdown to get the user ready
  CircleNode * circle;
public:
	/**
	 * Initialize the background layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

	TimedTransitionLayer(cocos2d::Rect * gameBounds);

	static TimedTransitionLayer * create(cocos2d::Rect * gameBounds);
};

}

#endif // __TIMED_TRANSITION_LAYER_H__
