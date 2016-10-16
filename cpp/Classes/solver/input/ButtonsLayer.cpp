#include "ButtonsLayer.h"


namespace QUAT {


ButtonsLayer * ButtonsLayer::create(cocos2d::Rect * gameBounds, float fontSize)
{
    ButtonsLayer *pRet = new(std::nothrow) ButtonsLayer(gameBounds, fontSize);
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

void ButtonsLayer::updateFromModel(Game * game) {
    auto user = game->getUser();
    auto puzzle = game->getPuzzle();

    // We have to adjust the step count in the UI by one
    int stepCount = puzzle->getStepCount() - 1;

    // Same with the steps layer
    this->stepsIndicatorLayer->setVisible(stepCount > 0);

    // Updates the count of steps
    this->stepsIndicatorLayer->update(stepCount);

    // Shows the over indicator if the user is over par
    this->stepsIndicatorLayer->setOverPar(puzzle->getStepCount() >= puzzle->getPar());

}
bool ButtonsLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }

    // Calculates all of the necessary ratios
    float width = gameBounds->size.width,
          height = gameBounds->size.height,
          wordSize = fontSize,
          outerDistance = (width / 2) * 0.8;

    this->stepsIndicatorLayer = StepsIndicatorLayer::create(fontSize);
    this->stepsIndicatorLayer->setPositionX(gameBounds->origin.x + (width / 2));
    this->stepsIndicatorLayer->setPositionY(height * Q_STEPTEXT_DOWN_Y);
    this->addChild(this->stepsIndicatorLayer);


    float skipSize = fontSize * 0.7;
    this->skipButtonLayer = SkipButtonLayer::create(skipSize);
    this->skipButtonLayer->setPositionX((width / 2) + outerDistance);
    this->skipButtonLayer->setPositionY(height * Q_STEPTEXT_DOWN_Y);
    this->addChild(this->skipButtonLayer);

    // Indicates we initialized successfully
    return true;
}

ButtonsLayer::ButtonsLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}



}
