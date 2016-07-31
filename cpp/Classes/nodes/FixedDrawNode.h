#ifndef __FIXED_DRAW_NODE_H__
#define __FIXED_DRAW_NODE_H__

#include "cocos2d.h"

namespace QUAT {

class FixedDrawNode : public cocos2d::Layer
{
public:
	cocos2d::DrawNode * node;

	virtual bool init();
	
	FixedDrawNode();
	
	static FixedDrawNode * create();
};

}

#endif // __FIXED_DRAW_NODE_H__
