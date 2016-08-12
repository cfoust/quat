#include "Definition.h"


namespace QUAT {

float Definition::getTotalHeight() {
           // Gets the word's line height
    return this->word->getLineHeight()
           // Then adds in the definition's height
           + this->definition->getLineHeight() 
           * this->definition->getStringNumLines();
}

Definition * Definition::create(float fontSize, float width) {
    Definition *pRet = new(std::nothrow) Definition(fontSize, width);
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Definition::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }

    float width = this->width, // The total width of the definition
          letterWidth = 0.8;   // The width of the letters as a proportion of
                               // their font size (different for every font)

    
    // Creates the head word, which is just the word in question
    float wordSize = this->fontSize * 0.8;
    this->word = cocos2d::Label::createWithTTF("AWOL", Q_FONT_PATH, wordSize);
    
    // Set the anchor point to be the top left
    this->word->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));

    // Puts the word at the far left boundary of the definition
    this->word->setPosition(-1 * width / 2, 0);

    // Justifies the text to the left and top
    this->word->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
    this->addChild(this->word);


    // Creates the part of speech text
    float posSize = this->fontSize * 0.4;
    this->pos = cocos2d::Label::createWithTTF("adjective", Q_FONT_PATH, posSize);
    
    // Give the text some opacity
    this->pos->setOpacity(120);
    
    // Sets the anchor point to the bottom left
    this->pos->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));

    // Puts it on the right side of the word
    this->pos->setPosition(this->word->getPositionX() + (letterWidth * wordSize * 4), 
                           this->word->getPositionY() - (wordSize));
    
    // Justifies the text to the left and top
    this->pos->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
    this->addChild(this->pos);

    // Create the actual definition
    float defSize = this->fontSize * 0.5;
    this->definition = cocos2d::Label::createWithTTF(
        "absent from one's post but without intent to desert.", Q_FONT_PATH, defSize);
    
    // Sets the anchor point to the top left
    this->definition->setAnchorPoint(cocos2d::Vec2(0.0f, 1.0f));
    
    // Forces the text to wrap to the width of the definition
    this->definition->setMaxLineWidth(width);

    // No idea what this does, but yolo
    this->definition->setClipMarginEnabled(false);

    // Changes the line height to be a little bit closer
    this->definition->setLineHeight(defSize);
    
    // Puts this just below the head word
    this->definition->setPosition(this->word->getPositionX(), 
                                  this->word->getPositionY() - wordSize);
    
    // Justifies the text to the left and top
    this->definition->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
    
    this->addChild(this->definition);

    
    // Indicates we initialized successfully
    return true;
}

Definition::Definition(float fontSize, float width) {
	this->fontSize = fontSize;
    this->width = width;
}



}