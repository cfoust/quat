#ifndef __KEYBOARD_LAYER_H__
#define __KEYBOARD_LAYER_H__

#include "cocos2d.h"

#include "WordNode.h"
#include "BorderedWordNode.h"
#include "../menu/MenuButton.h"

namespace QUAT {

class KeyboardLayer : public cocos2d::Layer
{
private:
	// Bounds of the game that we render in
	cocos2d::Rect * gameBounds;

	cocos2d::Rect * bounds;

	std::vector<MenuButton*> * buttons;

	float fontSize, keyboardHeight;

	int indexForPoint(cocos2d::Vec2 * point);

public:
	/**
	 * Initialize the solution layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();
	
	KeyboardLayer(cocos2d::Rect * gameBounds, float fontSize);

	void none();

	/**
	 * @brief      Get the top boundary (y coordinate) of the keyboard.
	 *
	 * @return     The top.
	 */
	float getHeight();

	/**
	 * Checks whether a point is in the keyboard.
	 */
	bool pointInKeyboard(cocos2d::Vec2 * point);

	/**
	 * Checks whether the point is in a letter.
	 */
	bool pointInLetter(cocos2d::Vec2 * point);

	/**
	 * Gets the string for the letter the point is in.
	 */
	std::string getLetter(cocos2d::Vec2 * point);
	
	static KeyboardLayer * create(cocos2d::Rect * gameBounds, float fontSize);
};

}

#endif // __KEYBOARD_LAYER_H__
