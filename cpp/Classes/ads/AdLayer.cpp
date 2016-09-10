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

    float adSize = height * .33;
    this->adPlaceholder = RectRadius::create(300, 
                                             250,
                                             0, 
                                             0, 
                                             true);
    this->adPlaceholder->setPosition(width / 2, height / 2);
    this->addChild(this->adPlaceholder);

    float titleSize = wordSize * 0.72;
    this->adTitle = cocos2d::Label::createWithTTF("Advertisement", Q_FONT_PATH, titleSize * 0.5);
    this->adTitle->setPosition(gameBounds->origin.x + (width / 2), 
                               (height / 2) + (250 / 2) + (titleSize / 2));
    this->addChild(this->adTitle);


    this->skipText = cocos2d::Label::createWithTTF("You can skip this ad in 10 seconds.", Q_FONT_PATH, titleSize * 0.5);
    this->skipText->setPosition(gameBounds->origin.x + (width / 2), 
                               (height / 2) - (250 / 2) - (titleSize / 2));
    this->addChild(this->skipText);
    
    // Indicates we initialized successfully
    return true;
}

void AdLayer::startTimer() {
    this->secondsRemaining = 10;
    this->schedule(schedule_selector(AdLayer::updateTime), 1.0f);
    this->skipText->setString("You can skip this ad in 10 seconds.");
    this->closeButton->setVisible(false);
}

void AdLayer::updateTime(float dt) {
    std::ostringstream stringStream;
    this->secondsRemaining--;
    stringStream << "You can skip this ad in " << this->secondsRemaining << " seconds.";

    std::string copyOfStr = stringStream.str();
    
    this->skipText->setString(copyOfStr);

    if (this->secondsRemaining == 0) {
        this->unschedule( schedule_selector(AdLayer::updateTime));
        this->closeButton->setVisible(true);
        this->skipText->setString("Tap the X in the upper left to close.");
    }

}

AdLayer::AdLayer(cocos2d::Rect * gameBounds, float fontSize, CloseButton * closeButton) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
    this->closeButton = closeButton;
}



}