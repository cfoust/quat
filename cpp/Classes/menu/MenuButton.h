#ifndef __MENU_BUTTON_H__
#define __MENU_BUTTON_H__

#include "cocos2d.h"
#include "../nodes/RectRadius.h"

namespace QUAT {

class MenuButton : public cocos2d::Layer
{
private:
	float fontSize,
		  width,
		  height;

	bool _enabled,
		 _selected,
		 _trackingTouch,
		 _showBorder;

	std::function<void(void)> callback;

	cocos2d::Label * textLabel;
	// The default and selected colors for the borders
	cocos2d::Color4B * defaultColor,
					 * selectedColor;

	cocos2d::Rect * bounds;

	RectRadius * border,
			   * background;

	std::string title;

	bool contains(cocos2d::Touch* touch);

	void regenerateBounds();

public:
	virtual bool init();	

	/**
	 * Sets the enabled status of the button. Enabled buttons can receive
	 * events.
	 */
	void enabled(bool status);

	cocos2d::Rect * getBounds();

	/**
	 * Returns whether or not the button is enabled.
	 */
	bool isEnabled();

	/**
	 * Sets the selected status of the button. Selected means that the border
	 * is highlighted.
	 */
	void selected(bool selected);


	bool isSelected();

	void showBorder(bool showBorder);

	/**
	 * Sets the text of the button.
	 */
	void setText(std::string text);

	/**
	 * Gets the text of the button.
	 */
	const std::string getText();

	void setPositionX(float x);
	void setPositionY(float y);
	
	MenuButton(std::string title, 
			   float fontSize, 
			   float width, 
			   float height,
			   std::function<void(void)> callback);
	
	static MenuButton * create(std::string title, 
							   float fontSize, 
							   float width, 
							   float height,
							   std::function<void(void)> callback);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

}

#endif // __MENU_BUTTON_H__
