#ifndef __TEXT_INDICATOR_LAYER_H__
#define __TEXT_INDICATOR_LAYER_H__

#include "cocos2d.h"
#include "../../Constants.h"

#include <string>

namespace QUAT {

class TextIndicatorLayer : public cocos2d::Layer
{
private:
	cocos2d::Label * text;

	float fontSize;

public:

	/**
	 * @brief      Fades in and displays a string.
	 *
	 * @param      str   The string
	 */
	void display(std::string str);

	/**
	 * @brief      Sets the string without any animation.
	 *
	 * @param[in]  str   The string
	 */
	void setText(std::string str);

	/**
	 * Initialize the solution layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();
	
	TextIndicatorLayer(float fontSize);
	
	static TextIndicatorLayer * create(float fontSize);
};

}

#endif // __TEXT_INDICATOR_LAYER_H__
