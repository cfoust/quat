#ifndef __TIMED_LAYER_H__
#define __TIMED_LAYER_H__

#include "cocos2d.h"
#include "../Constants.h"

#include "TimedCard.h"
#include "MenuButton.h"
#include "../models/Game.h"

namespace QUAT {

USING_NS_CC;

class TimedLayer : public cocos2d::Layer
{
private:
  float fontSize,
  // The size of the card that displays information about
  // the user's endless mode progress
        cardWidth,
        cardHeight;

  // Timed Mode header
	cocos2d::Label * headerLabel;

  MenuButton * continueButton;

  // Shows progress information
  TimedCard * card;

public:
	virtual bool init();

	TimedLayer(float fontSize,
               float cardWidth,
               float cardHeight);

  void updateFromModel(Game * game);

	static TimedLayer * create(float fontSize,
                               float cardWidth,
                               float cardHeight);
};

}
#endif // __TIMED_LAYER_H__

