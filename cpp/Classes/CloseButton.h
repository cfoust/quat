#ifndef __CLOSE_BUTTON_H__
#define __CLOSE_BUTTON_H__

#include "cocos2d.h"
#include "Constants.h"

#include "Clickable.h"

namespace QUAT {

class CloseButton : public Clickable
{
private:
	float size;

	std::function<void(void)> callback;

	// Node to draw the cross
	cocos2d::DrawNode * node;

	void up();
	void entered();
	void left();

	void drawCross();
public:
	virtual bool init();
	
	CloseButton(float size);
	
	static CloseButton * create(float size);
};

}

#endif // __CLOSE_BUTTON_H__
