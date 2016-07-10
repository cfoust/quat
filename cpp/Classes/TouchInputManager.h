#ifndef __TOUCH_INPUT_MANAGER_H__
#define __TOUCH_INPUT_MANAGER_H__

#include "cocos2d.h"

namespace QUAT {

class TouchInputManager
{
protected:
	// The last place the user started touching
	cocos2d::Vec2 * lastDown;

	// Whether or not this manager is enabled
	bool enabled = true;

public:
	TouchInputManager();

	void setEnabled(bool enabled);

	bool getEnabled();

	void inputBegan(cocos2d::Vec2 * point);

	void inputMoved(cocos2d::Vec2 * point);

	void inputDone(cocos2d::Vec2 * point);

	virtual void began(cocos2d::Vec2 * point) = 0;
	virtual void moved(cocos2d::Vec2 * point) = 0;
	virtual void done(cocos2d::Vec2 * point) = 0;
};

}

#endif // __TOUCH_INPUT_MANAGER_H__
