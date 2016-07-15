#ifndef __SOLVER_KEYBOARD_MANAGER_H__
#define __SOLVER_KEYBOARD_MANAGER_H__

#include "cocos2d.h"
#include "../models/Game.h"

namespace QUAT {

class PuzzleLayer;
class SolverStateController;

class SolverKeyboardManager
{
private:
	SolverStateController * sc;
	Game * model;
	PuzzleLayer * puzzleLayer;
	int lastColumn;
	
public:
	SolverKeyboardManager(SolverStateController * sc, 
							Game * model, 
							PuzzleLayer * puzzleLayer);

	void input(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

}

#endif // __SOLVER_KEYBOARD_MANAGER_H__
