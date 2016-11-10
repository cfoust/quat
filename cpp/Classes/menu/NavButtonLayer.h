#ifndef __NAV_BUTTON_LAYER_H__
#define __NAV_BUTTON_LAYER_H__

#include "cocos2d.h"
#include "../Constants.h"
#include "../Clickable.h"

USING_NS_CC;
namespace QUAT {

class NavButtonLayer : public Clickable
{
private:
  // The large icon used in the center of the button
	Sprite * icon;
  
  // The title shown just under the button
  Label * title;

  const char * titleText,  // The text of the title
             * file;   // The filename of the icon

  // The size of one side of the icon
  float iconSize,
        textSize;

	void up();
	void entered();
	void left();
public:
	bool init();
	
	NavButtonLayer(const char *file, const char * title, float iconSize, float textSize);
	static NavButtonLayer * create(const char *file, const char * title, float iconSize, float textSize);
};

}

#endif // __NAV_BUTTON_LAYER_H__
