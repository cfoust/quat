#ifndef __BANNER_BUTTON_LAYER_H__
#define __BANNER_BUTTON_LAYER_H__

#include "cocos2d.h"
#include "../../../Clickable.h"

namespace QUAT {

class BannerButtonLayer : public Clickable
{
private:
	// The banner sprite in the background of the layer
	cocos2d::Sprite * background;

	// The text label that shows the current rank
	cocos2d::Label * textLabel;

	cocos2d::DrawNode * node;

	// Stores the integer value reflecting the rank text on the banner
	int value;

	// The height of the banner sprite
	float _height;

	// The various callbacks needed for being a Clickable
	void up();
	void entered();
	void left();

	/**
	 * @brief      Updates the text on the banner to match the value stored by
	 *             this->value.
	 */
	void updateText();

	/**
	 * @brief      Animates the banner moving up, changing the text, and then
	 *             moving down.
	 */
	void animateChange(int toVal);

	/**
	 * @brief      Animate moving down in rank.
	 *
	 * @param[in]  toVal  The to value
	 */
	void rankDown(int toVal);

	/**
	 * @brief      Animate moving up in rank.
	 *
	 * @param[in]  toVal  The to value
	 */
	void rankUp(int toVal);
	
public:
	bool init();
	
	BannerButtonLayer(float height);
	
	static BannerButtonLayer * create(float height);

	void update(int newVal);
};

}

#endif // __BANNER_BUTTON_LAYER_H__
