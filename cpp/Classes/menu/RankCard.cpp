#include "RankCard.h"

#include <string>

USING_NS_CC;

namespace QUAT {

RankCard * RankCard::create(float fontSize,
               float width,
               float height)
{
    RankCard *pRet = new(std::nothrow) RankCard(fontSize,
                                                    width,
                                                    height);
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


void RankCard::update(int currentRank, float progressPercent) {
  this->displayRank(currentRank);
  this->setProgressPercent(progressPercent);
}
void RankCard::displayRank(int currentRank) {
   this->drawnBanner->update(currentRank);
   this->leftLabel->setString(std::to_string(currentRank)); 
   this->rightLabel->setString(std::to_string(currentRank + 1)); 
}

void RankCard::setProgressPercent(float percent) {
    percent = percent < 0.08 ? 0.08 : percent;
    float newWidth = percent * this->progressBarWidth;

    this->progressFG->setWidth(newWidth);
    this->progressFG->setPositionX((this->_width / 2) -
                                   (this->progressBarWidth / 2) +
                                   (newWidth / 2));
}

bool RankCard::init() {
	// Init the super class
    if ( !cocos2d::Layer::init() )
    {
        return false;
    }


    float borderRadius = this->_width * 0.05,
          borderWidth = this->_width *  0.008;

    // Set the default color
    this->defaultColor = new cocos2d::Color4B(255,255,255,64);
    this->fillInColor = new cocos2d::Color4B(255,255,255,120);

    // Creates the white border around the edges
    this->border = RectRadius::create(this->_width, this->_height, borderRadius, borderWidth, false);
    this->border->setPositionX(this->_width / 2);
    this->border->setPositionY(this->_height / 2);
    this->border->setColor(cocos2d::Color4B::WHITE);
    this->addChild(this->border, 1);

    // Creates the background layer
    this->background = RectRadius::create(this->_width, this->_height, borderRadius, borderWidth, true);
    this->background->setPositionX(this->_width / 2);
    this->background->setPositionY(this->_height / 2);
    this->background->setColor(*this->defaultColor);
    this->addChild(this->background, 0);

    // Create the progress bar
    float progressBarWidth = this->_width * 0.8,
          progressBarHeight = this->_height * 0.05,
          progressBarY = this->_height * 0.2;

    this->progressBarWidth = progressBarWidth;
    this->progressBG = RectRadius::create(progressBarWidth, progressBarHeight, progressBarHeight * 0.6, 0,  true);
    this->progressBG->setPositionX(this->_width / 2);
    this->progressBG->setPositionY(progressBarY);
    this->progressBG->setColor(*this->fillInColor);
    this->addChild(this->progressBG, 1);

    this->progressFG = RectRadius::create(progressBarWidth, progressBarHeight, progressBarHeight * 0.6, 0,  true);
    this->progressFG->setPositionX(this->_width / 2);
    this->progressFG->setPositionY(progressBarY);
    this->progressFG->setColor(cocos2d::Color4B::WHITE);
    this->addChild(this->progressFG, 1);
    this->setProgressPercent(0.6);

    float labelSize = this->fontSize * 0.32;
    this->leftLabel = cocos2d::Label::createWithTTF("1", Q_FONT_PATH, labelSize);
    this->leftLabel->setPositionX((this->_width / 2) - (progressBarWidth * 0.48));
    this->leftLabel->setPositionY(progressBarY + labelSize);
    this->addChild(this->leftLabel, 2);

    this->rightLabel = cocos2d::Label::createWithTTF("2", Q_FONT_PATH, labelSize);
    this->rightLabel->setPositionX((this->_width / 2) + (progressBarWidth * 0.48));
    this->rightLabel->setPositionY(progressBarY + labelSize);
    this->addChild(this->rightLabel, 2);

    float bannerWidth = this->_width * 0.12,
          bannerHeight = this->_height * 0.5;
    this->drawnBanner = DrawnBanner::create(bannerWidth, bannerHeight, this->fillInColor);
    this->drawnBanner->setPositionX((this->_width / 2) - bannerWidth / 2);
    this->drawnBanner->setPositionY(this->_height - bannerHeight);
    this->addChild(this->drawnBanner, 1);
    return true;
}

RankCard::RankCard(float fontSize,
               float width,
               float height)
{
  	this->fontSize = fontSize;
    this->_width = width;
    this->_height = height;
}


};
