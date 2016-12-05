#ifndef __PROGRESS_INDICATOR_LAYER_H__
#define __PROGRESS_INDICATOR_LAYER_H__

#include "cocos2d.h"
#include "../../Constants.h"
#include "../../nodes/ProgressBar.h"
namespace QUAT {

class ProgressIndicatorLayer : public cocos2d::Layer
{
private:
	cocos2d::Label * leftText,
	      			   * rightText;

  ProgressBar * progress;

  float fontSize, barWidth;

	cocos2d::Color4B * defaultColor,
                  * fillInColor;
public:
	bool init();
  
  void displayRank(int currentRank);

  void setProgressPercent(float percent);

  void update(int currentRank, float progressPercent);

  void animate();

	ProgressIndicatorLayer(float fontSize, float barWidth);

	static ProgressIndicatorLayer * create(float fontSize, float barWidth);

	/**
	 * Sets the opacity of the rect.
	 * @param opacity [description]
	 */
	void setOpacity(GLubyte opacity);
};

}

#endif // __PROGRESS_INDICATOR_LAYER_H__
