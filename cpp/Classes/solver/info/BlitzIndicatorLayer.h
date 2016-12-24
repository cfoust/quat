#ifndef __BLITZ_INDICATOR_LAYER_H__
#define __BLITZ_INDICATOR_LAYER_H__

#include "cocos2d.h"
#include "../../Constants.h"
#include "../../nodes/CircleNode.h"
#include "../../models/Game.h"
#include "../../models/Theme.h"

#define PI 3.14159265

namespace QUAT {

class BlitzIndicatorLayer : public cocos2d::Layer
{
private:
	cocos2d::Label * topText,
                 * bottomText;
  CircleNode * circle;

  float fontSize,
        percent;

  void setPercent(float p);

public:
  void setScheme(ColorScheme scheme);

	bool init();
  
  void updateFromModel(Game * game);

	BlitzIndicatorLayer(float fontSize);

	static BlitzIndicatorLayer * create(float fontSize);

	/**
	 * Sets the opacity of the rect.
	 * @param opacity [description]
	 */
	void setOpacity(GLubyte opacity);
};

}

#endif // __BLITZ_INDICATOR_LAYER_H__
