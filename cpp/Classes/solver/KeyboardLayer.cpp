#include "KeyboardLayer.h"
#include "../menu/MenuButton.h"

#include <string>

USING_NS_CC;

namespace QUAT {

KeyboardLayer * KeyboardLayer::create(cocos2d::Rect * gameBounds, float fontSize)
{
    KeyboardLayer *pRet = new(std::nothrow) KeyboardLayer(gameBounds, fontSize);
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

void KeyboardLayer::none() {
}


bool KeyboardLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Calculates all of the necessary ratios
    float width = gameBounds->size.width,
    	  height = gameBounds->size.height,
    	  keyboardHeight = height * 0.3,
          keyboardY = 0,
          ratio = 2.265,
          keyboardWidth = ratio * keyboardHeight;

    if (width < keyboardWidth) {
        keyboardWidth = width;
        keyboardHeight = (1 / ratio) * keyboardWidth;
    }

    // Calculates the rest of them
    float halfWidth = keyboardWidth / 2,
          keyHeight = keyboardHeight * 0.27,
          keyFontSize = keyHeight * 0.6,
          keyWidth = keyboardWidth * 0.080,
          verticalGap = keyboardHeight * 0.07,
          horizontalGap = keyboardWidth * 0.02;

    std::string rows[] = {
        "QWERTYUIOP",
        "ASDFGHJKL",
        "ZXCVBNM"
    };
    float offsets[3] = {
        0,
        keyboardWidth * 0.05,
        keyboardWidth * 0.16
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < rows[i].length(); j++) {
            auto button = MenuButton::create(std::string(1, rows[i].at(j)),
                                         keyFontSize,
                                         keyWidth,
                                         keyHeight,
                                         CC_CALLBACK_0(KeyboardLayer::none, this));
            button->setPositionX((width / 2) 
                                 + offsets[i] 
                                 + (j * (horizontalGap + keyWidth))
                                 - halfWidth + (horizontalGap / 2));
            button->setPositionY(((3 - (i + 1)) * (keyHeight + verticalGap))
                                 + (height * 0.02) + keyboardY);
            this->addChild(button);
        }
    }


    return true;
}

KeyboardLayer::KeyboardLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}

}