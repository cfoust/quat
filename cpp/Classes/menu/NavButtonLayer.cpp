#include "NavButtonLayer.h"

namespace QUAT {
void NavButtonLayer::up() {
	cocos2d::log("test");
}

void NavButtonLayer::entered() {
}
void NavButtonLayer::left() {
}
bool NavButtonLayer::init() {
	// Init the super class
  if ( !Clickable::init() )
  {
      return false;
  }

  // Initialize the icon
  this->icon = cocos2d::Sprite::create(this->file);

  // Initialize some callbacks
  this->enterCallback = CC_CALLBACK_0(NavButtonLayer::entered, this);
  this->leaveCallback = CC_CALLBACK_0(NavButtonLayer::left, this);

  // Rescale it to the proper size
  float height = this->iconSize,
      width = height,
      scale = height / this->icon->getBoundingBox().size.height,
      textOffset = this->textSize;

  // Initialize and scale the icon
  this->icon->setScale(scale,scale);
  //this->icon->setPositionX(-width / 4);
  this->icon->setPositionY((height / 2) + textOffset);
  this->addChild(this->icon, 1);

  this->title = Label::createWithTTF(this->titleText, Q_FONT_PATH, this->textSize);
  this->addChild(this->title, 2);

  // Set up the bounds
  this->setHeight(height + textOffset);
  this->setWidth(width);
  this->setOffset(this->iconSize/ -2, this->iconSize/ -2);

	return true;
}


NavButtonLayer::NavButtonLayer(const char *file, const char * title, float iconSize, float textSize) {
  this->iconSize = iconSize;
  this->textSize = textSize;
  this->titleText = title;
  this->file = file;
}


NavButtonLayer * NavButtonLayer::create(const char *file, const char * title, float iconSize, float textSize)
{
    NavButtonLayer *pRet = new(std::nothrow) NavButtonLayer(file, title, iconSize, textSize);
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

}
