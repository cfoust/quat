#ifndef __PUZZLE_LAYER_H__
#define __PUZZLE_LAYER_H__

#include "cocos2d.h"
#include "../models/Game.h"
#include "WordNode.h"
#include "BorderedWordNode.h"
#include "BannerButtonLayer.h"
#include "UndoButtonLayer.h"
#include "StepsIndicatorLayer.h"
#include "KeyboardLayer.h"

namespace QUAT {
class SolverStateController;
class SolverTouchInputManager;
class SolverKeyboardManager;
class PuzzleLayer : public cocos2d::Layer
{
private:
	Game * game;

	// The goal word and current word
	WordNode * goalWord;
	BorderedWordNode * currentWord;

	// The various layers that handle other aspects of the game UI
	BannerButtonLayer * bannerButton;
	
	KeyboardLayer * keyboardLayer;
	bool keyboardUp;

	UndoButtonLayer * undo;
	StepsIndicatorLayer * stepsLayer;

	// Contains the bounds of the game (just the portrait part) handed down
	// by the global context
	cocos2d::Rect * gameBounds;

	// Stores the font size given to us by the global context. Most graphical
	// calculations are based on this so that you could adjust it if you wanted
	// to.
	float fontSize;

	float stepStart,   // The y-position of the steps indicator when the 
	                   // keyboard is hidden.  
		  stepFinish;  // The y-position of the steps indicator when the 
		               // keyboard is shown.

	// Handles various aspects of UI state control. Usually used for
	// larger-scale view manipulation while still staying within the game.
	// Things like displaying a definition, the keyboard being shown, 
	SolverStateController * solverStateController;

	// Manages all of the touches that come into the layer as a whole, but not
	// necessarily on specific elements.
	SolverTouchInputManager * solverTouchInputManager;

	// Whether or not this layer is tracking a specific touch at a given time. 
	bool trackingTouch;

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    	// On desktop platforms, allows the user to manipulate the game using
    	// context-sensitive key bindings. Useful for rapidly solving puzzles
    	// and to test things.
    	SolverKeyboardManager * solverKeyboardManager;
    #endif
    
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
	
	/**
	 * @brief      Called when the user clicks the banner.
	 */
	void bannerClick();

	/**
	 * @brief      Called when the user clicks on the undo button.
	 */
	void undoClick();

	/**
	 * @brief      Animates the keyboard appearing and sets it to be 
	 *             interactable.
	 */
	void raiseKeyboard();

	/**
	 * @brief      Animates the keyboard disappearing and disables 
	 *             interactability.
	 */
	void lowerKeyboard();

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
