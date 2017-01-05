#ifndef __ICON_MENU_BUTTON_H__
#define __ICON_MENU_BUTTON_H__

#include "cocos2d.h"
#include "../Constants.h"
#include "MenuButton.h"

namespace QUAT {

using namespace std;

class IconMenuButton : public MenuButton
{
private:
  // Necessary for putting an icon on the button
  cocos2d::Sprite * icon;
  float iconHeight;
  string iconFile;

public:
	virtual bool init();
	
	IconMenuButton(string iconFile,
                float iconHeight,
                float width,
                float height,
                float borderRadius,
                float borderWidth);
	
	static IconMenuButton * create(string iconFile,
                                 float iconHeight,
                                 float width,
                                 float height,
                                 float borderRadius,
                                 float borderWidth);
};

}

#endif // __ICON_MENU_BUTTON_H__
