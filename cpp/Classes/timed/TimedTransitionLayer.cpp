#include "TimedTransitionLayer.h"

namespace QUAT {


TimedTransitionLayer * TimedTransitionLayer::create(cocos2d::Rect * gameBounds,
                       Game * game,
                       GameStateController * GSC)
{
    TimedTransitionLayer *pRet = new(std::nothrow) TimedTransitionLayer(gameBounds, game, GSC);
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

TimedTransitionLayer::TimedTransitionLayer(cocos2d::Rect * gameBounds,
                       Game * game,
                       GameStateController * GSC) {
  this->gameBounds = gameBounds;
  this->game = game;
  this->GSC = GSC;
}

void TimedTransitionLayer::reset() {
  this->timeLeft = 3;
}

MenuButton * TimedTransitionLayer::initializeRankButton(float fontSize, 
                                                        float width, 
                                                        float height,
                                                        float borderRadius,
                                                        float borderWidth) {
  auto button = MenuButton::create("", fontSize, width, height, borderRadius, borderWidth);
  this->addChild(button);

  return button;
}

void TimedTransitionLayer::handleRankClick(int button) {
  this->game->getUser()->getTimedState()->setWinRank(button);
  this->updateFromModel();
}

void TimedTransitionLayer::rankButtonCallback2() {
  handleRankClick(2);
}

void TimedTransitionLayer::rankButtonCallback4() {
  handleRankClick(4);
}

void TimedTransitionLayer::rankButtonCallback8() {
  handleRankClick(8);
}

void TimedTransitionLayer::updateFromModel() {
  auto state = this->game->getUser()->getTimedState();
  int winRank = state->getWinRank();

  // Enable the buttons
  this->rank2Button->setEnabled(winRank != 2);
  this->rank4Button->setEnabled(winRank != 4);
  this->rank8Button->setEnabled(winRank != 8);
}

bool TimedTransitionLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  float width          = gameBounds->size.width,
        height         = gameBounds->size.height,
        circleSize     = height * 0.1,
        circleFontSize = circleSize * 1.6,
        circleY        = height * 0.6;
  
  // The circle that animates the time remaining in the combo
  this->circle = CircleNode::create(circleSize);
  this->circle->setColor(cocos2d::Color4B(255, 255, 255, 40));
  this->circle->setPosition(width / 2, circleY);
  this->addChild(this->circle, 2);

  this->topText = cocos2d::Label::createWithTTF("3", Q_FONT_PATH, circleFontSize);
  this->topText->setOpacity(40);
  this->topText->setPosition(width / 2, circleY);
  this->topText->setColor(cocos2d::Color3B::WHITE);

  this->bottomText = cocos2d::Label::createWithTTF("3", Q_FONT_PATH, circleFontSize);
  this->bottomText->setColor(cocos2d::Color3B::WHITE);
  this->bottomText->setOpacity(40);
  this->bottomText->setPosition(width / 2, circleY);
  this->addChild(bottomText, 1);

  // Sets up the clipping for the main multiplier text
  auto clip = cocos2d::ClippingNode::create();
  clip->setStencil(this->circle->getNode());
  clip->setInverted(false);
  clip->addChild(this->topText);
  clip->setPosition(width / 2, circleY);
  this->addChild(clip, 3);

  float raceTextSize = height * 0.03,
        raceTextY = circleY - (circleSize * 2);
  this->raceText = cocos2d::Label::createWithTTF("RACE TO RANK", Q_FONT_PATH, raceTextSize);
  this->raceText->setPosition(width / 2, raceTextY);
  this->addChild(raceText, 1);

  // Initialize all of the buttons
  float buttonWidth = width * 0.2,
        buttonHeight = buttonWidth  * 0.6,
        buttonFontSize = buttonHeight * 0.8,
        buttonBorderRadius = buttonWidth * 0.1,
        buttonBorderWidth = buttonWidth * 0.02,
        buttonY = raceTextY - buttonHeight - raceTextSize;

  this->rank2Button = initializeRankButton(buttonFontSize,
                                           buttonWidth,
                                           buttonHeight,
                                           buttonBorderRadius,
                                           buttonBorderWidth);
  this->rank4Button = initializeRankButton(buttonFontSize,
                                           buttonWidth,
                                           buttonHeight,
                                           buttonBorderRadius,
                                           buttonBorderWidth);
  this->rank8Button = initializeRankButton(buttonFontSize,
                                           buttonWidth,
                                           buttonHeight,
                                           buttonBorderRadius,
                                           buttonBorderWidth);
  float buttonIncrement = width / 4,
        buttonWidthHalf = buttonWidth / 2;

  // Set the buttons at thirds to each other
  this->rank2Button->setPositionX(buttonIncrement - buttonWidthHalf);
  this->rank4Button->setPositionX(buttonIncrement * 2 - buttonWidthHalf);
  this->rank8Button->setPositionX(buttonIncrement * 3 - buttonWidthHalf);

  this->rank2Button->setPositionY(buttonY);
  this->rank4Button->setPositionY(buttonY);
  this->rank8Button->setPositionY(buttonY);

  this->rank2Button->upCallback = CC_CALLBACK_0(TimedTransitionLayer::rankButtonCallback2, this);
  this->rank4Button->upCallback = CC_CALLBACK_0(TimedTransitionLayer::rankButtonCallback4, this);
  this->rank8Button->upCallback = CC_CALLBACK_0(TimedTransitionLayer::rankButtonCallback8, this);

  // Change their strings
  this->rank2Button->setText("2");
  this->rank4Button->setText("4");
  this->rank8Button->setText("8");

  
  // Get updates
  this->scheduleUpdate();

  return true;
}

void TimedTransitionLayer::update(float delta) {
  // Don't do anything if the user is playing endless
  if (this->game->getUser()->isPlayingEndless()) return;

  if (this->timeLeft > 0) {
    // Add the delta
    this->timeLeft -= delta;

    // Set the circle's text
    int secs = (int) ceil(timeLeft);
    auto secString = std::to_string(secs);
    this->topText->setString(secString);
    this->bottomText->setString(secString);

    // Set the circle's percentage
    this->circle->setPercent(this->timeLeft / TRANS_SECS);

    // Means the addition of the current delta pushed
    // us below zero; this will only run once in a reset
    if (this->timeLeft < 0) {
      // Get the user state
      auto state = this->game->getUser()->getTimedState();
      state->setRunning(true);
      this->GSC->setState(S_PuzzleSolver);
    }
  }
}

}

