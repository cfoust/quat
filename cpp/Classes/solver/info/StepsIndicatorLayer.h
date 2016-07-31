#ifndef __STEPS_INDICATOR_LAYER_H__
#define __STEPS_INDICATOR_LAYER_H__

#include "cocos2d.h"

namespace QUAT {

class StepsIndicatorLayer : public cocos2d::Layer
{
private:
	cocos2d::Label * subtext,
				   * stepText,
				   * overText;

	float fontSize;
public:
	bool init();

	/**
	 * @brief      Changes the view to reflect when the solution exceeds
	 *             the ideal length.
	 *
	 * @param[in]  overPar  Whether or not to display the over par mechanisms.
	 */
	void setOverPar(bool overPar);

	/**
	 * @brief      Updates the step count to the integer specified by num.
	 *
	 * @param[in]  num   The number.
	 */
	void update(int num);
	
	StepsIndicatorLayer(float fontSize);
	
	static StepsIndicatorLayer * create(float fontSize);

};

}

#endif // __STEPS_INDICATOR_LAYER_H__
