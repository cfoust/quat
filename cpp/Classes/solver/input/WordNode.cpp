#include "WordNode.h"

#include <vector>
#include <string>

namespace QUAT {

void WordNode::changeLetter(int column, std::string letter) {
	auto letterLabel = (*this->letterPool)[column];

	// Set the letter label to this letter
	letterLabel->setString(letter);
	this->word->replace(column, 1, letter, 0, 1);
}

void WordNode::changeWord(std::string * word) {
	for (int i = 0; i < 4; i++) {
		// Grab the letter in the word string
		std::string sub = word->substr(i, 1);

		auto letterLabel = (*this->letterPool)[i];

		this->changeLetter(i, sub);
	}
}

const std::string * WordNode::getLetter(int column) {
	return &(*this->letterPool)[column]->getString();
}

std::string * WordNode::getWord() {
	// Have to create a string and update it
	return this->word;
}

bool WordNode::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }
	
	float offset = -1 * (this->fontGap * 1.505);

	// Initialize the whole bounds
	whole = new cocos2d::Rect(0,0,0,0);

	// Initialize the pool of letters
	letterPool = new std::vector<cocos2d::Label*>();

	// Initialize the bounds of the letters
	bounds = new std::vector<cocos2d::Rect*>();

	for (int i = 0; i < 4; i++) {
		auto letterLabel = cocos2d::Label::createWithTTF("A", Q_FONT_PATH, this->fontSize);

		// Set them to their proper location
		letterLabel->setPositionX((((float) i) * this->fontGap) + offset);
		letterLabel->setPositionY(0);

		// Make them white
		letterLabel->setColor(cocos2d::Color3B(255, 255, 255));

		this->addChild(letterLabel);

		letterPool->push_back(letterLabel);
		bounds->push_back(new cocos2d::Rect(0,0,0,0));
	}

	this->word = new std::string("AAAA");


	this->recalculateBounds();

	return true;
}

bool WordNode::pointInWhole(cocos2d::Point * point) {
	return this->whole->containsPoint(*point);
}

int WordNode::pointInWord(cocos2d::Point * point) {
	for (int i = 0; i < 4; i++) {
		auto rect = (*this->bounds)[i];

		if (rect->containsPoint(*point)) {
			return 3-i;
		}
	}

	return -1;
}

void WordNode::recalculateBounds() {
	// Initialize all the pretty calculations
	float x = this->getPositionX(),
		  y = this->getPositionY(),
		  fontHeight = this->fontSize,
		  fontHeightHalf = fontHeight / 2,
		  fontWidth = fontHeight * 0.8,
		  fontWidthHalf = fontWidth / 2;

	// Calculate bound rectangles for all of the letters
	for (int i = 0; i < 4; i++) {
		auto letter = (*this->letterPool)[i];
		auto rect = (*this->bounds)[i];

		rect->setRect(x - letter->getPositionX() - fontWidthHalf,
					  y - fontHeightHalf,
					  fontWidth,
					  fontHeight);
	}

	auto first = (*this->bounds)[0],
		 last  = (*this->bounds)[3];

	whole->setRect(first->origin.x,
				   first->origin.y,
				   ((last->origin.x + last->size.width) - first->origin.x),
				   first->size.height);
  this->setContentSize(cocos2d::Size(((last->origin.x + last->size.width) - first->origin.x),
                                       first->size.height));
}

void WordNode::setOpacity(GLubyte opacity) {
	Layer::setOpacity(opacity);

	for (int i = 0; i < 4; i++) {
		auto label = (*this->letterPool)[i];
		label->setOpacity(opacity);
	}
}

WordNode::WordNode(float fontSize, float fontGap) {
	this->fontSize = fontSize;
	this->fontGap = fontGap;
}

WordNode * WordNode::create(float fontSize, float fontGap)
{
    WordNode *pRet = new(std::nothrow) WordNode(fontSize, fontGap);
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

}
