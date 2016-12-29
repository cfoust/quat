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


void MenuLayer::resetLayout() {
  float width = gameBounds->size.width,
        height = gameBounds->size.height,
        totalHeight = 0,
        padding     = 20;

  // A bit of padding on top
  totalHeight += padding;

  // Add the card for timed mode
  auto size = this->timedCard->getContentSize();
  this->timedCard->setPosition((width / 2) - (size.width / 2),
                              totalHeight);
  totalHeight += size.height;
  totalHeight += padding; // Some extra padding before the QUAT logo

  // Add the rank card for endless mode
  this->rankCard->setPosition((width / 2) - (size.width / 2),
                              totalHeight);
  totalHeight += size.height;
  totalHeight += padding * 2;
  
  // Add the QUAT logo
  size = this->quatLogo->getContentSize();
  // Since the anchor is centered vertically, we add half the height on both
  // sides
  totalHeight += size.height / 2;
  this->quatLogo->setPosition((width / 2),
                              totalHeight);
  totalHeight += size.height / 2;
  totalHeight += padding * 2;
  
  scrollView->setInnerContainerSize( Size( width, totalHeight ) );
  // Adjust the scroll view if there's less stuff than is needed
  float difference = height - totalHeight;
  scrollView->setEnabled(difference < 0);

  // Reset the position to the bottom if we're going to leave it scrollable
  if (difference < 0) {
    difference = 0;
  } 
  
  // Move the scrollView up if necessary
  scrollView->setPositionY(difference);
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
  
  // Sets up the scroll view
  auto sv = ui::ScrollView::create();
  this->scrollView = sv;
  sv->setContentSize( Size( width, height ) );
  sv->setInnerContainerSize( Size( width, height * 2 ) );

  // Initializes the current word, which is the word the user is currently
  // operating on
  float proportion = 0.6;
  this->quatLogo = BorderedWordNode::create(wordSize * proportion, gap * proportion);
  this->quatLogo->changeWord(new std::string("QUAT"));
  sv->addChild(this->quatLogo);
  
  float cardWidth = width * 0.8,
        cardHeight = cardWidth * 0.32;
  this->rankCard = RankCard::create(wordSize, cardWidth, cardHeight);
  sv->addChild(this->rankCard);

  this->timedCard = TimedCard::create(wordSize, cardWidth, cardHeight);
  sv->addChild(this->timedCard);

  // Add the scroll view to the layer
  this->addChild(sv);

  this->resetLayout();

  // Indicates we initialized successfully
  return true;
}

MenuLayer::MenuLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}



}
