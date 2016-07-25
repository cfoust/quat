#ifndef __MENU_BUTTON_H__
#define __MENU_BUTTON_H__

#include "cocos2d.h"
#include "../Clickable.h"
#include "../nodes/RectRadius.h"

namespace QUAT {

class MenuButton : public Clickable
{
private:
	float fontSize,
		  _width,
		  _height;

	bool _enabled,
		 _selected,
		 _showBorder;

	std::function<void(void)> callback;

	cocos2d::Label * textLabel;
	// The default and selected colors for the borders
	cocos2d::Color4B * defaultColor,
					 * selectedColor;


	RectRadius * border,
			   * background;

	std::string title;

	/**
	 * @brief      When the touch enters this button.
	 */
	void entered();

	/**
	 * @brief      When the touch leaves this button.
	 */
	void left();

public:
	virtual bool init();

	cocos2d::Rect * getBounds();

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
};

}

#endif // __MENU_BUTTON_H__
