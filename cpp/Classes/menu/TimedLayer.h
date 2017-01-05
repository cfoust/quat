#ifndef __TIMED_LAYER_H__
#define __TIMED_LAYER_H__

#include "cocos2d.h"
#include "../Constants.h"

#include "TimedCard.h"
#include "IconMenuButton.h"
#include "../models/Game.h"
#include "../models/TimeUtils.h"

namespace QUAT {

USING_NS_CC;

#define TIME_DEFAULT "??:??.???"

class TimedLayer : public cocos2d::Layer
{
private:
  float fontSize,
  // The size of the card that displays information about
  // the user's endless mode progress
        sectionWidth,
        sectionHeight;

  // Timed Mode header
	cocos2d::Label * headerLabel,
                 * rank2Label,
                 * rank4Label,
                 * rank8Label,
                 * time2Label,
                 * time4Label,
                 * time8Label;


  // Shows progress information
  TimedCard * card;

public:
  IconMenuButton * playButton,
                 * continueTopButton,
                 * restartButton;

	virtual bool init();

	TimedLayer(float fontSize,
             float sectionWidth,
             float sectionHeight);

  void updateFromModel(Game * game);

	static TimedLayer * create(float fontSize,
                             float sectionWidth,
                             float sectionHeight);
};

}
#endif // __TIMED_LAYER_H__

