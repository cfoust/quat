#include "AdLayer.h"


namespace QUAT {


AdLayer * AdLayer::create(cocos2d::Rect * gameBounds, float fontSize, CloseButton * closeButton)
{
    AdLayer *pRet = new(std::nothrow) AdLayer(gameBounds, fontSize, closeButton);
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

bool AdLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }

    // Calculates all of the necessary ratios
    float width = gameBounds->size.width,
          height = gameBounds->size.height,
          wordSize = fontSize,
          gap = wordSize * Q_LETTER_GAP;

    // Initializes the current word, which is the word the user is currently
    // operating on
    float proportion = 0.6;
    this->quatLogo = BorderedWordNode::create(wordSize * proportion, gap * proportion);
    this->quatLogo->changeWord(new std::string("QUAT"));
    this->quatLogo->setPosition(gameBounds->origin.x + (width / 2),
                                height * 0.9);
    this->addChild(this->quatLogo);


    float menuButtonOffset = width * Q_MENUBTN_OFFSET;  // Where the close button is
    this->skipText = cocos2d::Label::createWithTTF("10", Q_FONT_PATH, wordSize * 0.8);
    this->skipText->setPosition(gameBounds->origin.x + menuButtonOffset,
                               height - menuButtonOffset);
    this->addChild(this->skipText);

    float cardWidth = width * 0.8,
          cardHeight = cardWidth * 0.32;
    this->rankCard = RankCard::create(wordSize, cardWidth, cardHeight);
    this->rankCard->setPosition(gameBounds->origin.x + (width / 2) - (cardWidth / 2),
                                height * 0.7);
    this->addChild(this->rankCard);

    float adSize = height * .33;
    this->adPlaceholder = RectRadius::create(300,
                                             250,
                                             0,
                                             0,
                                             true);
    this->adPlaceholder->setPosition(width / 2, ((height * 0.7) / 2));
    this->addChild(this->adPlaceholder);

    // Indicates we initialized successfully
    return true;
}

void AdLayer::startTimer() {
    this->secondsRemaining = 10;
    this->schedule(schedule_selector(AdLayer::updateTime), 1.0f);
    this->skipText->setString("10");
    this->closeButton->setVisible(false);
}

void AdLayer::updateTime(float dt) {
    std::ostringstream stringStream;
    this->secondsRemaining--;

    this->skipText->setString(std::to_string(this->secondsRemaining));

    if (this->secondsRemaining == 0) {
        this->unschedule( schedule_selector(AdLayer::updateTime));
        this->closeButton->setVisible(true);
        this->skipText->setString("");
    }

}


void AdLayer::updateFromModel(Game * game) {
  auto user = game->getUser();
  this->rankCard->update(user->getDisplayRank(), user->getRankProgress());
}
AdLayer::AdLayer(cocos2d::Rect * gameBounds, float fontSize, CloseButton * closeButton) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
    this->closeButton = closeButton;
}



}
