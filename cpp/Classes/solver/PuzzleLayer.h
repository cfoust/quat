#ifndef __PUZZLE_LAYER_H__
#define __PUZZLE_LAYER_H__

#include "cocos2d.h"
#include "../models/Game.h"
#include "SolutionLayer.h"
#include "KeyboardLayer.h"

namespace QUAT {
class SolverStateController;
class SolverTouchInputManager;
class SolverKeyboardManager;
class PuzzleLayer : public cocos2d::Layer
{
private:
	Game * game;

	cocos2d::Rect * gameBounds;
	float fontSize;

	SolutionLayer * solutionLayer;
	KeyboardLayer * keyboardLayer;

	SolverStateController * solverStateController;
	SolverTouchInputManager * solverTouchInputManager;

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    SolverKeyboardManager * solverKeyboardManager;
    #endif

	bool trackingTouch;
public:
	// ##################################################
	// ######METHODS USED FOR STATE TRANSITIONS##########
	// ##################################################

	/**
	 * Resets the UI to the idle state.
	 */
	void goIdle();

	/**
	 * Allows user to choose letter at given index.
	 * @param column Column to choose.
	 */
	void chooseLetter(int column);

	// ##################################################
	// ##### METHODS USED FOR VIEW MANIPULATION #########
	// ##################################################
	
	// Most of these are just passthroughs to other classes
	void changeCurrentLetter(int column, std::string letter);

	/**
	 * Checks whether this point falls in a letter in the current word, which
	 * means we may have to change one of the letters.
	 * @param  point Point we want to check.
	 * @return       -1 if the point isn't in any letter, otherwise 0-3
	 *                corresponds to the letter the point is in.
	 */
	int pointInCurrentWord(cocos2d::Vec2 * point);

	/**
	 * Gets a pointer to the current word displayed by the current word.
	 */
	std::string * getCurrentWord();

	/**
	 * Checks whether the point is in the general area of the keyboard.
	 * @param  point Point we want to check.
	 * @return       Whether or not the point is in the keyboard.
	 */
	bool pointInKeyboard(cocos2d::Vec2 * point);

	/**
	 * Checks whether the point is in a letter on the keyboard.
	 * @param  point Point we want to check.
	 * @return       Whether or not the point is in a letter on the keyboard.
	 */
	bool pointInKeyboardLetter(cocos2d::Vec2 * point);

	/**
	 * Gets the letter the point is in and returns it.
	 * @param  point Point we want to check.
	 * @return       String representation of the letter the point is in.
	 */
	std::string getKeyboardLetter(cocos2d::Vec2 * point);

	/**
	 * Finishes the word being chosen.
	 */
	void finishWord();

	/**
	 * Updates the game layer with information from the model.
	 */
	void updateFromModel();

	// ##################################################
	// ############# NORMAL CLASS METHODS ###############
	// ##################################################

	/**
	 * Initialize the background layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

	PuzzleLayer(cocos2d::Rect * gameBounds, float fontSize);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, 
								      cocos2d::Event* event);
	
	/**
	 * Creates a PuzzleLayer object.
	 */
	static PuzzleLayer * create(cocos2d::Rect * gameBounds, float fontSize);
};

}

#endif // __PUZZLE_LAYER_H__
