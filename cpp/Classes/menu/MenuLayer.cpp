#include "MenuLayer.h"


namespace QUAT {


MenuLayer * MenuLayer::create(cocos2d::Rect * gameBounds, float fontSize)
{
    MenuLayer *pRet = new(std::nothrow) MenuLayer(gameBounds, fontSize);
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

void MenuLayer::updateFromModel(Game * game) {
  auto user = game->getUser();
  this->rankCard->update(user->getDisplayRank(), user->getRankProgress());
}


void MenuLayer::storeCallback() {
}

void MenuLayer::creditsCallback() {
}

bool MenuLayer::init() {
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
    
    float cardWidth = width * 0.8,
          cardHeight = cardWidth * 0.32;
    this->rankCard = RankCard::create(wordSize, cardWidth, cardHeight);
    this->rankCard->setPosition(gameBounds->origin.x + (width / 2) - (cardWidth / 2), 
                                height * 0.7);
    this->addChild(this->rankCard);

    float buttonIconSize = wordSize * 1.2,
          buttonTextSize = buttonIconSize * 0.3;

    this->storeButton = NavButtonLayer::create("menu-buttons/store.png", "Store", buttonIconSize, buttonTextSize);
    this->storeButton->setPosition(width / 2, height /2);
    this->storeButton->upCallback = CC_CALLBACK_0(MenuLayer::storeCallback, this);
    this->addChild(this->storeButton);

    this->creditsButton = NavButtonLayer::create("menu-buttons/credits.png", "Credits", buttonIconSize, buttonTextSize * 0.7);
    this->creditsButton->setPosition(width / 2, (height / 2) - (buttonIconSize * 2 + buttonTextSize));
    this->creditsButton->upCallback = CC_CALLBACK_0(MenuLayer::creditsCallback, this);
    this->addChild(this->creditsButton);

    // Indicates we initialized successfully
    return true;
}

MenuLayer::MenuLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}



}
