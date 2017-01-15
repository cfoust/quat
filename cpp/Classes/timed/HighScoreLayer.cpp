#include "HighScoreLayer.h"

namespace QUAT {


HighScoreLayer * HighScoreLayer::create(Game * game,
                                        cocos2d::Rect * gameBounds,
                                        GameStateController * GSC)
{
    HighScoreLayer *pRet = new(std::nothrow) HighScoreLayer(game, gameBounds, GSC);
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

void HighScoreLayer::updateFromModel() {
  auto state = game->getUser()->getTimedState();

  // Set the time the user completed the challenge in
  this->scoreText->setString(TimeUtils::formatMs(state->getTime()));

  // Set up the banner
  auto winRank = state->getWinRank();
  this->banner->update(winRank);

  auto high  = state->getHighScore(winRank),
       score = state->getTime();
  
  // Whether or not the user beat their high score
  bool beat = high == score;
  this->highScoreText->setVisible(beat);
  this->winParticles->setVisible(beat);

  if (beat) {
    this->winParticles->resumeEmissions();
  } else {
    this->winParticles->pauseEmissions();
  }
}

void HighScoreLayer::restartCallback() {
  auto user = game->getUser();

  // Reset the state of timed mode
  user->getTimedState()->reset();

  // Move to the puzzle solver state
  this->GSC->setState(S_TimedTransition);
}


HighScoreLayer::HighScoreLayer(Game * game,
                               cocos2d::Rect * gameBounds,
                               GameStateController * GSC) {
  this->game = game;
  this->gameBounds = gameBounds;
  this->GSC = GSC;
}

bool HighScoreLayer::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  float width          = gameBounds->size.width,
        height         = gameBounds->size.height,
        fontSize       = height * 0.10;

  // The text that shows the time the user completed at
  this->scoreText = cocos2d::Label::createWithTTF(TimeUtils::formatMs(1000 * 60 * 61), Q_FONT_PATH, fontSize);
  this->scoreText->setPosition(width / 2, height * 0.65);
  this->scoreText->setOpacity(65);
  this->addChild(this->scoreText);

  float highScoreSize = fontSize / 2;
  this->highScoreText = Label::createWithTTF("HIGH SCORE!", Q_FONT_PATH, highScoreSize);
  this->highScoreText->setPosition(width / 2, height * 0.50);
  this->highScoreText->setVisible(false);
  this->addChild(this->highScoreText);

  float bannerWidth  = width * 0.2,
        bannerHeight = height * 0.15;

  // The banner that shows the goal rank
  this->banner = DrawnBanner::create(bannerWidth, bannerHeight);
  this->banner->setPositionX((width / 2) - bannerWidth / 2);
  this->banner->setPositionY(height - bannerHeight);
  this->addChild(this->banner, 1);

  // The restart button to try again
  float buttonWidth         = width * 0.2,
        buttonHeight        = buttonWidth,
        buttonIconHeight    = buttonHeight * 0.4,
        borderRadius        = 0.12 * buttonWidth,
        borderWidth         = 0.03 * buttonWidth;

  this->restartButton = IconMenuButton::create("undo.png",
                                           buttonIconHeight,
                                           buttonWidth,
                                           buttonHeight,
                                           borderRadius,
                                           borderWidth);

  this->restartButton->setPositionX((width / 2) - (buttonWidth / 2));
  this->restartButton->setPositionY(height * 0.2);
  this->addChild(this->restartButton);
  this->restartButton->upCallback = CC_CALLBACK_0(HighScoreLayer::restartCallback, this);


  // Create a temporary star node to generate the texture for the particles
  float starSize = width * 0.05;
  auto node = IconNode::create(ICON_STAR, starSize);

  this->winParticles = ParticleSystemQuad::createWithTotalParticles(400);
  winParticles->retain();
  this->addChild(winParticles, 10);

  // Set the particle system to the node's texture
  winParticles->setTexture(node->toTexture());


  winParticles->setDuration(-1);
  // gravity
  winParticles->setGravity(Vec2(0, -200));

  // angle
  winParticles->setAngle(90);
  winParticles->setAngleVar(180);

  // speed of particles
  winParticles->setSpeed(160);
  winParticles->setSpeedVar(20);

  // emitter position
  winParticles->setPosition( Vec2(width / 2, height * 1.3) );
  winParticles->setPosVar(Vec2::ZERO);

  // life of particles
  winParticles->setLife(20);
  winParticles->setLifeVar(1);

  // spin of particles
  winParticles->setStartSpin(0);
  winParticles->setStartSizeVar(0);
  winParticles->setEndSpin(0);
  winParticles->setEndSpinVar(0);

  winParticles->setStartColor(Color4F::WHITE);
  winParticles->setEndColor(Color4F::WHITE);

  // size, in pixels
  winParticles->setStartSize(starSize);
  winParticles->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

  // emits per second
  winParticles->setEmissionRate(winParticles->getTotalParticles()/winParticles->getLife());

  // additive
  winParticles->setBlendAdditive(true);

  // hide it
  winParticles->pauseEmissions();
  winParticles->setVisible(false);

  return true;
}


}

