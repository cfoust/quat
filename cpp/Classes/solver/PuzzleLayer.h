#ifndef __PUZZLE_LAYER_H__
#define __PUZZLE_LAYER_H__

#include "cocos2d.h"
#include "SolutionLayer.h"
#include "KeyboardLayer.h"

namespace QUAT {
class SolverStateController;
class PuzzleLayer : public cocos2d::Layer
{
private:
	cocos2d::Rect * gameBounds;
	float fontSize;

	SolutionLayer * solutionLayer;
	KeyboardLayer * keyboardLayer;

	SolverStateController * solverStateController;
public:
	/**
	 * Initialize the background layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

	/**
	 * Resets the UI to the idle state.
	 */
	void goIdle();

	/**
	 * Allows user to choose letter at given index.
	 * @param column Column to choose.
	 */
	void chooseLetter(int column);

	PuzzleLayer(cocos2d::Rect * gameBounds, float fontSize);
	
	/**
	 * Creates a PuzzleLayer object.
	 */
	static PuzzleLayer * create(cocos2d::Rect * gameBounds, float fontSize);
};

}

#endif // __PUZZLE_LAYER_H__
