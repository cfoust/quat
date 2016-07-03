#ifndef __SOLUTION_LAYER_H__
#define __SOLUTION_LAYER_H__

#include "cocos2d.h"

#include "WordNode.h"
#include "BorderedWordNode.h"

namespace QUAT {

class SolutionLayer : public cocos2d::Layer
{
private:
	// Bounds of the game that we render in
	cocos2d::Rect * gameBounds;

	WordNode * goalWord;
	BorderedWordNode * currentWord;

	// The font size for this layer
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
