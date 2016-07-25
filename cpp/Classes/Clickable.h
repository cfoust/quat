#ifndef __CLICKABLE_H__
#define __CLICKABLE_H__

#include "cocos2d.h"

namespace QUAT {

class Clickable : public cocos2d::Layer
{
protected:
	// The bounds of the clickable area to check against
	cocos2d::Rect * bounds;

	
	bool inside,  // Whether or not the touch is inside
		 tracking,// Whether we're tracking a click 
		 enabled; // Whether or not this layer is accepting clicks

	float width, height;

	
	std::function<void(void)> leaveCallback, // When the click leaves (even if not down)
							  enterCallback,	 // When the click is down and in the bounds
							  upCallback; 	 // When the click goes up and was in the bounds

	// Called by this class to regenerate the click bounds when this layer
	// is moved and resized
	void recalculateBounds();

	// Handle all of the touch events for this object
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    bool contains(cocos2d::Touch* touch);

public:
	bool init();
	
	Clickable();
	
	static Clickable * create();

	// We override these methods (from Layer) to regenerate the bounds
	void setPosition(const cocos2d::Vec2 & position);
	void setPosition(float x, float y);
	void setPositionX(float x);
	void setPositionY(float y);

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
};

}

#endif // __CLICKABLE_H__
