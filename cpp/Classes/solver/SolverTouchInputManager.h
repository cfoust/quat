#ifndef __SOLVER_TOUCH_INPUT_MANAGER_H__
#define __SOLVER_TOUCH_INPUT_MANAGER_H__

#include "cocos2d.h"
#include "../TouchInputManager.h"
#include "../models/Game.h"

namespace QUAT {

class PuzzleLayer;
class SolverStateController;

class SolverTouchInputManager : TouchInputManager
{
private:
	SolverStateController * sc;
	Game * model;
	PuzzleLayer * puzzleLayer;
	int lastColumn;

	void finishWord();
public:
	SolverTouchInputManager(SolverStateController * sc, 
							Game * model, 
							PuzzleLayer * puzzleLayer);

	void began(cocos2d::Vec2 * point);
	void moved(cocos2d::Vec2 * point);
	void done(cocos2d::Vec2 * point);
};

}

#endif // __SOLVER_TOUCH_INPUT_MANAGER_H__
