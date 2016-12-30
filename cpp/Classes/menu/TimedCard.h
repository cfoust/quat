#ifndef __TIMED_CARD_H__
#define __TIMED_CARD_H__

#include "cocos2d.h"
#include "../Constants.h"
#include "DrawnBanner.h"
#include "../nodes/RectRadius.h"
#include "../nodes/ProgressBar.h"

namespace QUAT {

class TimedCard : public cocos2d::Layer
{
private:
	float fontSize,
		  _width,
		  _height,
      borderRadius,
      borderWidth;

	cocos2d::Color4B * defaultColor,
                  * fillInColor;

	RectRadius * border;

public:
	virtual bool init();

	TimedCard(float fontSize,
			   float width,
			   float height);

  float getBorderRadius();
  float getBorderWidth();

	static TimedCard * create(float fontSize,
							   float width,
							   float height);
};

}
#endif // __TIMED_CARD_H__
