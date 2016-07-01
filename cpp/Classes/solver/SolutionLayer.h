#ifndef __SOLUTION_LAYER_H__
#define __SOLUTION_LAYER_H__

#include "cocos2d.h"

namespace QUAT {

class SolutionLayer : public cocos2d::Layer
{
private:
	cocos2d::Rect * gameBounds;
	float fontSize;

public:
	/**
	 * Initialize the solution layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();
	
	SolutionLayer(cocos2d::Rect * gameBounds, float fontSize);
	
	static SolutionLayer * create(cocos2d::Rect * gameBounds, float fontSize);
};

}

#endif // __SOLUTION_LAYER_H__
