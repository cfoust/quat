#ifndef __ENDLESS_LAYER_H__
#define __ENDLESS_LAYER_H__

#include "cocos2d.h"
#include "../Constants.h"

#include "RankCard.h"
#include "IconMenuButton.h"
#include "../models/Game.h"

#include "../solver/input/BorderedWordNode.h"

namespace QUAT {

USING_NS_CC;

class EndlessLayer : public cocos2d::Layer
{
private:
  float fontSize,
  // The size of the card that displays information about
  // the user's endless mode progress
        sectionWidth,
        sectionHeight;

  // Endless Mode header
	cocos2d::Label * headerLabel;

  BorderedWordNode * freeText;
  
  // Shows progress information
  RankCard * card;

public:
  IconMenuButton * continueButton;

	virtual bool init();

	EndlessLayer(float fontSize,
               float sectionWidth,
               float sectionHeight);

  void updateFromModel(Game * game);

	static EndlessLayer * create(float fontSize,
                               float sectionWidth,
                               float sectionHeight);
};

}
#endif // __ENDLESS_LAYER_H__

