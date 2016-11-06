#ifndef __CLICKABLE_H__
#define __CLICKABLE_H__

#include "cocos2d.h"

namespace QUAT {

class Clickable : public cocos2d::Layer
{
protected:


	bool inside,  // Whether or not the touch is inside
		 tracking,// Whether we're tracking a click
		 enabled, // Whether or not this layer is accepting clicks
		 debug;

	float width, height;

  // The offsets for the click boundaries
  float xOffset, yOffset;

	// Handle all of the touch events for this object
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

  bool containsNodePoint(cocos2d::Vec2* point);
public:
  bool containsTouch(cocos2d::Touch* touch);
  bool containsPoint(cocos2d::Vec2* point);

	std::function<void(void)> leaveCallback, // When the click leaves (even if not down)
							  enterCallback,	 // When the click is down and in the bounds
							  upCallback; 	 // When the click goes up and was in the bounds

	bool init();

	Clickable();

	static Clickable * create();

  /**
   * Sets the offset for the click boundaries. These are added to the origin.
   * */
  void setOffset(float x, float y);

	/**
	 * @brief      Whether or not to print debug log for this clickable.
	 *
	 * @param[in]  debug  The debug
	 */
	void setDebug(bool debug);

	/**
	 * @brief      Sets the callback called when the user leaves the bounds
	 * 			   of this layer.
	 *
	 * @param[in]  callback  The callback
	 */
	void setLeaveCallback(std::function<void(void)> & callback);

	/**
	 * @brief      Sets the callback called when the user either enters or
	 * 			   clicks on these bounds.
	 *
	 * @param[in]  callback  The callback
	 */
	void setEnterCallback(std::function<void(void)> & callback);

	/**
	 * @brief      Sets the callback called when the user releases a tap within
	 * 			   the bounds of this layer.
	 *
	 * @param[in]  callback  The callback
	 */
	void setUpCallback(std::function<void(void)> & callback);

	/**
	 * @brief      Sets whether this Clickable object is accepting input.
	 *
	 * @param[in]  enabled  Whether or not this Clickable object is accepting
	 * 						input.
	 */
	void setEnabled(bool enabled);

	/**
	 * @brief      Set the width of the bound area.
	 *
	 * @param[in]  width  The width
	 */
	void setWidth(float width);

	/**
	 * @brief      Set the height of the bound area.
	 *
	 * @param[in]  height  The height
	 */
	void setHeight(float height);

	void setVisible(bool visible);
};

}

#endif // __CLICKABLE_H__
