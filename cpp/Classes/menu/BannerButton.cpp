#include "BannerButton.h"

#include <string>

USING_NS_CC;

namespace QUAT {

BannerButton * BannerButton::create(float width,
                                    float height,
                                    float borderRadius,
                                    float borderWidth)
{
    BannerButton *pRet = new(std::nothrow) BannerButton(width,
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

void BannerButton::updateBanner(int rank) {
  this->banner->update(rank);
}

bool BannerButton::init() {
	// Init the super class
  if ( !MenuButton::init() )
  {
      return false;
  }
  
  auto fillInColor = new cocos2d::Color4B(255,255,255,120);

  float bannerHeight = this->_height * 0.8,
        bannerWidth = bannerHeight * 0.8;
  this->banner = DrawnBanner::create(bannerWidth, bannerHeight, fillInColor);
  this->banner->setPositionX((this->_width / 2) - bannerWidth / 2);
  this->banner->setPositionY((this->_height / 2) - bannerHeight / 2);
  this->addChild(this->banner, 1);

  return true;
}

BannerButton::BannerButton(float width,
                           float height,
                           float borderRadius,
                           float borderWidth) :
              MenuButton("", 0, width, height, borderRadius, borderWidth)   {
}

}
