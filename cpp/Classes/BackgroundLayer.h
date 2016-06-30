#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"

namespace QUAT {

class BackgroundLayer : public cocos2d::Layer
{
public:
	/**
	 * Initialize the background layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();
	
	/**
	 * Syntactic sugar for hooking the creation function.
	 */
	CREATE_FUNC(BackgroundLayer);
};

}

#endif // __BACKGROUND_LAYER_H__
