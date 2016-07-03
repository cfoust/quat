#ifndef __CLICKABLE_H__
#define __CLICKABLE_H__

#include "cocos2d.h"

namespace QUAT {

class Clickable : public cocos2d::Layer
{
private:
	// Bounds of the game that we render in
	cocos2d::Rect * gameBounds;

	WordNode * goalWord;
	BorderedWordNode * currentWord;

	// The font size for this layer
	float fontSize;

public:
	virtual bool init();
	
	Clickable(cocos2d::Node parent);
	
	static Clickable * create(cocos2d::Node parent);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

}

#endif // __CLICKABLE_H__
