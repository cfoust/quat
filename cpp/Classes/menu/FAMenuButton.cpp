#include "FAMenuButton.h"

#include <string>

USING_NS_CC;

namespace QUAT {

FAMenuButton * FAMenuButton::create(const char16_t * icon,
                                    float iconHeight,
                                    float width,
                                    float height,
                                    float borderRadius,
                                    float borderWidth)
{
    FAMenuButton *pRet = new(std::nothrow) FAMenuButton(icon,
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


bool FAMenuButton::init() {
	// Init the super class
  if ( !MenuButton::init() )
  {
      return false;
  }

  // Create the icon
  this->iconNode = IconNode::create(icon, iconHeight);
  this->iconNode->setPositionX(this->_width / 2);
  this->iconNode->setPositionY(this->_height / 2);
  this->addChild(this->iconNode, 3);

  return true;
}

FAMenuButton::FAMenuButton(const char16_t * icon,
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
  this->icon = icon;
  this->iconHeight = iconHeight;
}

}
