#ifndef __THEME_H__
#define __THEME_H__

#include "cocos2d.h"

namespace QUAT {

class Game;

struct ColorScheme {
	cocos2d::Color3B top,      // The color the background gradient starts at
	                           // at the top of the screen
					 bottom;   // The color it finishes with at the bottom
};

class Theme
{
protected:
	// The current color scheme of the theme
	ColorScheme scheme;

	// Whether or not the color scheme has changed since the last call to 
	// getColorSchemeChanged()
	bool colorSchemeChanged;
public:
	/**
	 * @brief      Gets the current color scheme of this theme.
	 *
	 * @return     The color scheme.
	 */
	ColorScheme getColorScheme();

	/**
	 * @brief      Whether or not the color scheme changed as the result of a
	 *             call to update.
	 *
	 * @return     The color scheme changed.
	 */
	bool getColorSchemeChanged();

	/**
	 * @brief      Reads values on the game state to determine changes to the
	 *             color scheme or other members. 
	 *
	 * @param      model  The model
	 */
	virtual void update(Game * model);

	Theme();
};

}

#endif // __THEME_H__