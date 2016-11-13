#ifndef __INDICATOR_LAYER_H__
#define __INDICATOR_LAYER_H__

#include "cocos2d.h"
#include "../../Constants.h"

#include <string>

namespace QUAT {

USING_NS_CC;

class IndicatorLayer : public Layer
{
private:
	Label * text;

  // The done and perfect sprites
  Sprite * doneSprite,
         * perfectSprite;
  
  // Holds the dimensions of the game
    cocos2d::Rect * gameBounds;

	float fontSize;

public:

  // User finished a puzzle
  void done();

  // User finished a puzzle with a perfect number of steps
  void perfect();

  // User entered a word that isn't a real word
  void notAWord(std::string word);

	/**
	 * Initialize the solution layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

	IndicatorLayer(cocos2d::Rect * gameBounds, float fontSize);

	static IndicatorLayer * create(cocos2d::Rect * gameBounds, float fontSize);
};

}

#endif // __INDICATOR_LAYER_H__
