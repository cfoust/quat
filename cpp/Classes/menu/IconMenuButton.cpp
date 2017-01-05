#include "IconMenuButton.h"

#include <string>

USING_NS_CC;

namespace QUAT {

IconMenuButton * IconMenuButton::create(string iconFile,
                                        float iconHeight,
                                        float width,
                                        float height,
                                        float borderRadius,
                                        float borderWidth)
{
    IconMenuButton *pRet = new(std::nothrow) IconMenuButton(iconFile,
                                                            iconHeight,
                                                            width,
                                                            height,
                                                            borderRadius,
                                                            borderWidth);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool IconMenuButton::init() {
	// Init the super class
  if ( !MenuButton::init() )
  {
      return false;
  }

  // Create the icon
  this->icon = cocos2d::Sprite::create(iconFile);
  if (this->icon == NULL) return false;

  // Calculate how much we need to change the scale by checking
  // the sprite's height
  float scale = iconHeight / this->icon->getBoundingBox().size.height;
  this->icon->setScale(scale, scale);

  this->icon->setPositionX(this->_width / 2);
  this->icon->setPositionY(this->_height / 2);
  this->addChild(this->icon, 3);

  return true;
}

IconMenuButton::IconMenuButton(string iconFile,
                               float iconHeight,
                               float width,
                               float height,
                               float borderRadius,
                               float borderWidth) : 
                // Call the constructor for the MenuButton
                MenuButton("", 
                           0,
                           width, 
                           height, 
                           borderRadius, 
                           borderWidth) {
  this->iconHeight = iconHeight;
  this->iconFile = iconFile;
}

}
