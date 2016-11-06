#ifndef __PUZZLE_LAYER_H__
#define __PUZZLE_LAYER_H__

#include "cocos2d.h"

// The game model
#include "../models/Game.h"

// The Definition Layer
#include "../defs/DefinitionLayer.h"

// So we can control the background
#include "../BackgroundLayer.h"

// General menu button, not really sure if this should be used in this class
// yet but it's fine for right now
#include "MenuButtonLayer.h"

// All of the elements necessary for input to the game state
#include "input/WordNode.h"
#include "input/BorderedWordNode.h"
#include "input/UndoButtonLayer.h"
#include "input/KeyboardLayer.h"
#include "input/ButtonsLayer.h"

// info/ is for anything that just displays information to the user but is
// mostly non-interactive.
#include "info/banner/BannerButtonLayer.h"
#include "info/TextIndicatorLayer.h"
#include "info/DefinitionButtonLayer.h"
#include "info/StepsLayer.h"

namespace QUAT {

// All of the classes that need to be predefined.
class SolverStateController;
class SolverTouchInputManager;
class SolverKeyboardManager;
class GameStateController;

/**
 * @brief      PuzzleLayer is a layer that takes in the game bounds and builds
 *             an instance of the playable game. It handles the actual gameplay
 *             of QUAT and manipulates the game state in response to user input.
 */
class PuzzleLayer : public cocos2d::Layer
{
private:
	// A pointer to the game state.
	Game * game;

	// The background of the game. It is not in this object, but game-wide
	BackgroundLayer * background;

	// Controls the entire game so we can move to other screens
	GameStateController * GSC;

	// Stores the font size given to us by the global context. Most graphical
	// calculations are based on this so that you could adjust it if you wanted
	// to.
	float fontSize;

	// Contains the bounds of the game (just the portrait part) handed down
	// by the global context. All user interface elements in PuzzleLayer are
	// built inside these bounds.
	cocos2d::Rect * gameBounds;

	/*----------  User Input  ----------*/
	// The static UI element that shows the goal word of the puzzle.
	WordNode * goalWord;

	// The manipulatable element that the user changes to reach the word shown
	// by the goal word.
	BorderedWordNode * currentWord;


	// Undo button which lets the user go back a step in the solution.
	UndoButtonLayer * undo;

	// Keyboard layer that lets the user enter letters to manipulate the
	// current word. There is an animation that moves the keyboard up and down
	// when it is shown and hidden.
	KeyboardLayer * keyboardLayer;
	// Whether or not the keyboard is in its "up" position. Ensures that we do
	// not try and animate the keyboard upwards when it is already up.
	bool keyboardUp;
	float buttonsStart,   // The y-position of the steps indicator when the
	                   // keyboard is hidden.
		    buttonsFinish,  // The y-position of the steps indicator when the
		               // keyboard is shown.
        keyboardDownPos;  // The y-position of the keyboard when it is down.
	// Handles various aspects of UI state control. Usually used for
	// larger-scale view manipulation while still staying within the game.
	// Things like displaying a definition, the keyboard being shown,
	SolverStateController * solverStateController;

	// Manages all of the touches that come into the layer as a whole, but not
	// necessarily on specific elements.
	SolverTouchInputManager * solverTouchInputManager;

	// If true, process touch inputs
	bool enabled;

	// Whether or not this layer is tracking a specific touch at a given time.
	bool trackingTouch;

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    	// On desktop platforms, allows the user to manipulate the game using
    	// context-sensitive key bindings. Useful for rapidly solving puzzles
    	// and to test things.
    	SolverKeyboardManager * solverKeyboardManager;
    #endif

	/*----------  Information Display  ----------*/
	// The banner that shows the user's rank.
	BannerButtonLayer * bannerButton;

	// The button that allows the user to see the definition of words.
	DefinitionButtonLayer * definitionButton;

	// A generic animated text indicator that we use to congratulate the user
	// on completion of a puzzle and inform them when they attempt to use a word
	// that does not exist.
	TextIndicatorLayer * textLayer;

  ButtonsLayer * buttonsLayer;

	StepsLayer * stepsLayer;

public:

	/*===================================================
	=            UI State Transition Methods            =
	===================================================*/

	/**
	 * Resets the UI to the idle state.
	 */
	void goIdle();

	/**
	 * Allows user to choose letter at given index.
	 * @param column Column to choose.
	 */
	void chooseLetter(int column);

	/*=====  End of UI State Transition Methods  ======*/

	/*============================================================
	=            Methods for Responding to User Input            =
	============================================================*/

	/**
	 * @brief      Handles a touchBegan event. Passed as a callback to the
	 *             layer's event listener.
	 *
	 * @param      touch  The touch
	 * @param      event  The event
	 *
	 * @return     { description_of_the_return_value }
	 */
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	/**
	 * @brief      Handles a touchMoved event. Passed as a callback to the
	 *             layer's event listener.
	 *
	 * @param      touch  The touch
	 * @param      event  The event
	 */
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

    /**
     * @brief      Handles a touchEnded event. Passed as a callback to the
	 *             layer's event listener.
     *
     * @param      touch  The touch
     * @param      event  The event
     */
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    /**
     * @brief      Handles a keyPressed event. Only used when we are running
     *             natively on a desktop platform.
     *
     * @param[in]  keyCode  The key code
     * @param      event    The event
     */
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,
                      cocos2d::Event* event);
#endif

	/**
	 * @brief      Changes a letter at @column in the current word to the letter
	 *             given by @letter.
	 *
	 * @param[in]  column  The column
	 * @param[in]  letter  The letter
	 */
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
	 * @brief      Turns input on and off for most parts of this layer.
	 *
	 * @param[in]  enabled  Whether or not this layer should process input.
	 */
	void setEnabled(bool enabled);

	/**
	 * @brief      Grabs the word currently displayed by currentWord and tries
	 *             to add it into the current solution. Whether or not the
	 *             attempt is successful, this method updates the view to match
	 *             the game's model.
	 */
	void finishWord();

	/**
	 * @brief      Called when the user clicks the banner.
	 */
	void bannerClick();

	/**
	 * @brief      Called when the user clicks on the undo button.
	 */
	void undoClick();

	/**
	 * @brief      Called when the user clicks on the definition button.
	 */
	void definitionClick();

	/**
	 * @brief      Called when the user clicks on the skip button.
	 */
	void skipClick();

  void futureSightClick();

	/*=====  End of Methods for Responding to User Input  ======*/


	/*=================================================
	=            View Manipulation Methods            =
	=================================================*/

	/**
	 * Updates this layer with information from the model.
	 */
	void updateFromModel();

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

	/*=====  End of View Manipulation Methods  ======*/


	/**
	 * Initialize this layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

	PuzzleLayer(cocos2d::Rect * gameBounds,
				BackgroundLayer * background,
				float fontSize,
				Game * game,
				GameStateController * GSC);


	/**
	 * Creates a PuzzleLayer object.
	 */
	static PuzzleLayer * create(cocos2d::Rect * gameBounds,
						        BackgroundLayer * background,
								float fontSize,
								Game * game,
								GameStateController * GSC);
};

}

#endif // __PUZZLE_LAYER_H__
