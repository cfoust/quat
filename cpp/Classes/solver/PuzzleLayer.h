#ifndef __PUZZLE_LAYER_H__
#define __PUZZLE_LAYER_H__

#include "cocos2d.h"
#include "SolutionLayer.h"

namespace QUAT {

class PuzzleLayer : public cocos2d::Layer
{
private:
	cocos2d::Rect * gameBounds;
	float fontSize;

	QUAT::SolutionLayer * solutionLayer;
public:
	/**
	 * Initialize the background layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

	PuzzleLayer(cocos2d::Rect * gameBounds, float fontSize);
	
	/**
	 * Creates a PuzzleLayer object.
	 */
	static PuzzleLayer * create(cocos2d::Rect * gameBounds, float fontSize);
};

}

#endif // __PUZZLE_LAYER_H__
