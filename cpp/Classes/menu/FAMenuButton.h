#ifndef __FA_MENU_BUTTON_H__
#define __FA_MENU_BUTTON_H__

#include "cocos2d.h"
#include "../Constants.h"
#include "../nodes/IconNode.h"
#include "MenuButton.h"

namespace QUAT {

using namespace std;

class FAMenuButton : public MenuButton
{
private:
  const char16_t * icon;
  float iconHeight;

  IconNode * iconNode;

public:
	virtual bool init();
	
	FAMenuButton(char16_t * icon,
               float iconHeight,
               float width,
               float height,
               float borderRadius,
               float borderWidth);
	
	static FAMenuButton * create(char16_t * icon,
                               float iconHeight,
                               float width,
                               float height,
                               float borderRadius,
                               float borderWidth);
};

}

#endif // __FA_MENU_BUTTON_H__
