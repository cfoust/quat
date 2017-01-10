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

  auto score = state->getHighScore(winRank);
  this->scoreText->setString((score == 0) ? 
                              TIME_DEFAULT : 
                              TimeUtils::formatMs(score));
}

bool TimedTransitionLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  float width          = gameBounds->size.width,
        height         = gameBounds->size.height,
        circleSize     = height * 0.15,
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

  // Sets up the score text, which shows the current high score
  float scoreTextSize = height * 0.08,
        scoreY        = height * 0.3,
        scoreX        = width * 0.57,
        starX         = width * 0.17;
  this->scoreText = cocos2d::Label::createWithTTF(TIME_DEFAULT, Q_FONT_PATH, scoreTextSize);
  this->scoreText->setOpacity(180);
  this->scoreText->setPosition(scoreX, scoreY);
  this->scoreText->setColor(cocos2d::Color3B::WHITE);
  this->addChild(this->scoreText);

  // Sets up the star icon to show that the score is the best
  float starTextSize = scoreTextSize * 0.8;
  this->star = IconNode::create(ICON_STAR, starTextSize);
  this->star->setPosition(starX, scoreY);
  this->addChild(this->star, 2);

  // Initialize all of the buttons
  float buttonWidth = width * 0.2,
        buttonHeight = buttonWidth  * 1.2,
        buttonBorderRadius = buttonWidth * 0.1,
        buttonBorderWidth = buttonWidth * 0.02,
        buttonY = height * 0.1;

  this->rank2Button = BannerButton::create(buttonWidth,
                                           buttonHeight,
                                           buttonBorderRadius,
                                           buttonBorderWidth);
  this->rank2Button->updateBanner(2);
  this->addChild(this->rank2Button);

  this->rank4Button = BannerButton::create(buttonWidth,
                                           buttonHeight,
                                           buttonBorderRadius,
                                           buttonBorderWidth);
  this->rank4Button->updateBanner(4);
  this->addChild(this->rank4Button);

  this->rank8Button = BannerButton::create(buttonWidth,
                                           buttonHeight,
                                           buttonBorderRadius,
                                           buttonBorderWidth);
  this->rank8Button->updateBanner(8);
  this->addChild(this->rank8Button);

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

