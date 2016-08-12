#include "StepsLayer.h"

namespace QUAT {

void StepsLayer::update(std::vector<std::string> * steps) {
    int count = steps->size() - 2,
        index;

    for (int i = 0; i < 10; i++) {
        auto node = (*this->nodes)[i];

        index = (count - i);
        if (index < 0) {
            node->setVisible(false);
        } else {
            node->setVisible(true);
            node->changeWord(&steps->at(index));
        }
    }
}

bool StepsLayer::init() {
	// Init the super class
    if ( !cocos2d::Layer::init() )
    {
        return false;
    }

    float gap = this->fontSize * Q_LETTER_GAP;
    this->nodes = new std::vector<WordNode*>();
    for (int j = 0; j < 10; j++) {
        auto node = WordNode::create(this->fontSize, gap);

        // Cascade the words upwards
        node->setPositionY(j * this->fontSize * Q_WORDS_GAP * 0.7);
        
        this->addChild(node);
        this->nodes->push_back(node);
    }

    this->setOpacity(255);

	return true;
}

void StepsLayer::setOpacity(GLubyte opacity) {
    // Do the super call
    Layer::setOpacity(opacity);
    
    for (int j = 0; j < 10; j++) {
        auto node = (*this->nodes)[j];

        // Set the opacity of each node to still cascade
        node->setOpacity((int) floor(pow(0.5, j) * opacity));
    }
}

StepsLayer::StepsLayer(float fontSize) {
    this->fontSize = fontSize;
}


StepsLayer * StepsLayer::create(float fontSize)
{
    StepsLayer *pRet = new(std::nothrow) StepsLayer(fontSize);
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