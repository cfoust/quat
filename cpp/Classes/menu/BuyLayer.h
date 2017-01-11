#ifndef __BUY_LAYER_H__
#define __BUY_LAYER_H__

#include "cocos2d.h"
#include "../Constants.h"
#include "../models/Game.h"
#include "../nodes/RectRadius.h"
#include "../nodes/IconNode.h"
#include "MenuButton.h"
#include "FAMenuButton.h"

namespace QUAT {

USING_NS_CC;

class BuyLayer : public cocos2d::Layer
{
private:
  float sectionWidth,
        sectionHeight;

	RectRadius * border;

	Label * pleaLabel;

public:
  FAMenuButton * buyButton;

  void buyCallback();
  
	virtual bool init();

	BuyLayer(float sectionWidth,
           float sectionHeight);

  void updateFromModel(Game * game);

	static BuyLayer * create(float sectionWidth,
                           float sectionHeight);
};

}
#endif // __BUY_LAYER_H__

