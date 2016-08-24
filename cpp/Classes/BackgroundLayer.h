#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include "models/Theme.h"

namespace QUAT {

class BackgroundLayer : public cocos2d::Layer
{
private:
	cocos2d::LayerGradient * gradient;
public:
	/**
	 * Initialize the background layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

	/**
	 * @brief      Resets the color scheme of the gradient to the given scheme.
	 *
	 * @param      scheme  The scheme
	 */
	void setScheme(ColorScheme scheme);

	/**
	 * @brief      Animates to a new color scheme.
	 *
	 * @param      scheme  The scheme
	 */
	void animateScheme(ColorScheme scheme);
	
	/**
	 * Syntactic sugar for hooking the creation function.
	 */
	CREATE_FUNC(BackgroundLayer);
};

}

#endif // __BACKGROUND_LAYER_H__
