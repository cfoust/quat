#ifndef __PROGRESS_BAR_H__
#define __PROGRESS_BAR_H__

#include "cocos2d.h"
#include "RectRadius.h"


namespace QUAT {

class ProgressBar : public cocos2d::Layer
{
private:
	float width,  // Width of the rect
		    height; // Height of the rect

  // The foreground and background rects that make up the progress bar
	RectRadius * foreground,
			       * background;
public:

	/**
	 * Creates and returns a ProgressBar.
	 * @param  width        The width of the ProgressBar.
	 * @param  height       The height of the ProgressBar.
	 * @param  borderRadius The corner border radius.
	 * @param  borderWidth  The border thickness.
	 * @param  filled       Whether or not the rect is filled.
	 */
	static ProgressBar * create(float width, float height);
	
	bool init();
	
	ProgressBar(float width, float height);

	/**
	 * Sets the foreground color of the bar.
   * * @param color The new color.
	 */
	void setForegroundColor(const cocos2d::Color4B &color);

	/**
	 * Sets the background color of the bar.
   * * @param color The new color.
	 */
	void setBackgroundColor(const cocos2d::Color4B &color);


  void setPercent(float percent);
	/**
	 * Sets the opacity of the progress bar.
	 * @param opacity [description]
	 */
	void setOpacity(GLubyte opacity);
};

}

#endif // __PROGRESS_BAR_H__
