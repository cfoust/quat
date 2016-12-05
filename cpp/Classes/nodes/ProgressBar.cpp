#include "ProgressBar.h"

namespace QUAT {

ProgressBar * ProgressBar::create(float width, float height) {
	ProgressBar *pRet = new(std::nothrow) ProgressBar(width, height);

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

bool ProgressBar::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  float height = this->height,
        width  = this->width;

  this->background = RectRadius::create(width, height, height * 0.6, 0,  true);
  this->background->setPositionX(0);
  this->addChild(this->background, 1);

  this->foreground = RectRadius::create(width, height, height * 0.6, 0,  true);
  this->foreground->setPositionX(0);
  this->addChild(this->foreground, 1);

  return true;
}

ProgressBar::ProgressBar(float width, float height) {
	this->width = width;
	this->height = height;
}

void ProgressBar::setForegroundColor(const cocos2d::Color4B &color) {
  this->foregroundColor = color;
	this->foreground->setColor(color);
}

void ProgressBar::setBackgroundColor(const cocos2d::Color4B &color) {
  this->backgroundColor = color;
	this->background->setColor(color);
}

void ProgressBar::setPercent(float percent) {
  // Make sure the values are sane
  percent = (percent > 1.0) ? 1 : percent;
  percent = (percent < 0.0) ? 0 : percent;
  percent = percent < 0.08 ? 0.08 : percent;

  float newWidth = percent * this->width;

  this->foreground->setWidth(newWidth);
  this->foreground->setPositionX((this->width/ -2) + 
                                 (newWidth / 2));
}

void ProgressBar::setOpacity(GLubyte opacity) {
  Layer::setOpacity(opacity);
	this->foreground->setOpacity((opacity > foregroundColor.a) ? foregroundColor.a : opacity);
	this->background->setOpacity((opacity > backgroundColor.a) ? backgroundColor.a : opacity);
}

}
