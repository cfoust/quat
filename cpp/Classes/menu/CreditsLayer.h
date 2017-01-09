#ifndef __CREDITS_LAYER_H__
#define __CREDITS_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Constants.h"

#include "RankCard.h"
#include "IconMenuButton.h"
#include "../models/Game.h"

namespace QUAT {

USING_NS_CC;

class CreditsLayer : public cocos2d::Layer
{
private:
  float width, height;

  Label * text;

public:

	virtual bool init();

	CreditsLayer(float width, float height);

	static CreditsLayer * create(float width, float height);
};

}
#endif // __CREDITS_LAYER_H__

