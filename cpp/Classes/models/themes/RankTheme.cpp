#include "RankTheme.h"
#include "../Game.h"

namespace QUAT {

RankTheme::RankTheme() : Theme::Theme() {
  this->currentRank = -1;
}

void RankTheme::update(Game * model) {
  int rank = model->getUser()->getGameState()->getDisplayRank();

  // Rank has not changed since the last time this was called
  this->colorSchemeChanged = this->currentRank != rank;

	switch (rank) {
		case 1:
			this->scheme.top = cocos2d::Color3B(242,37,180);
			this->scheme.bottom = cocos2d::Color3B(80,80,255);
			break;
		case 2:
			this->scheme.top = cocos2d::Color3B(59,162,255);
			this->scheme.bottom = cocos2d::Color3B(246,130,223);
			break;
		case 3:
			this->scheme.top = cocos2d::Color3B(255,57,225);
			this->scheme.bottom = cocos2d::Color3B(225,196,0);
			break;
		case 4:
			this->scheme.top = cocos2d::Color3B(253,109,163);
			this->scheme.bottom = cocos2d::Color3B(149,0,135);
			break;
		case 5:
			this->scheme.top = cocos2d::Color3B(75,205,93);
			this->scheme.bottom = cocos2d::Color3B(248,68,123);
			break;
		case 6:
			this->scheme.top = cocos2d::Color3B(22,155,3);
			this->scheme.bottom = cocos2d::Color3B(207,192,80);
			break;
		case 7:
			this->scheme.top = cocos2d::Color3B(125,213,69);
			this->scheme.bottom = cocos2d::Color3B(2,168,194);
			break;
		case 8:
			this->scheme.top = cocos2d::Color3B(1,162,232);
			this->scheme.bottom = cocos2d::Color3B(40,35,107);
			break;
		case 9:
			this->scheme.top = cocos2d::Color3B(84,205,224);
			this->scheme.bottom = cocos2d::Color3B(104,44,146);
			break;
		case 10:
			this->scheme.top = cocos2d::Color3B(85,30,208);
			this->scheme.bottom = cocos2d::Color3B(150,5,9);
			break;
		case 11:
			this->scheme.top = cocos2d::Color3B(56,56,56);
			this->scheme.bottom = cocos2d::Color3B(177,177,177);
			break;
		case 12:
			this->scheme.top = cocos2d::Color3B(232,184,0);
			this->scheme.bottom = cocos2d::Color3B(156,87,0);
			break;
	}

  // Initialize to the first number we get on call
  if (this->currentRank == -1) {
    this->currentRank = rank;
  }
}

};
