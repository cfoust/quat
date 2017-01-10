#ifndef __BANNER_BUTTON_H__
#define __BANNER_BUTTON_H__

#include "cocos2d.h"
#include "../Constants.h"
#include "MenuButton.h"
#include "DrawnBanner.h"


namespace QUAT {

class BannerButton : public MenuButton
{
protected:
  DrawnBanner * banner;

public:
  void updateBanner(int rank);

	virtual bool init();

	void setEnabled(bool enabled) override;
	
	BannerButton(float width, 
               float height,
               float borderRadius,
               float borderWidth);
	
	static BannerButton * create(float width, 
                               float height,
                               float borderRadius,
                               float borderWidth);
};

}

#endif // __BANNER_BUTTON_H__
