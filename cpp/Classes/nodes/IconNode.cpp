#include "IconNode.h"

#include <cmath>
#define PI 3.14159265

namespace QUAT {

IconNode * IconNode::create(const char16_t * icon, float size) {
	IconNode *pRet = new(std::nothrow) IconNode(icon, size);

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

Label * IconNode::getLabel() {
  return this->text;
}
	
	
bool IconNode::init() {
	// Init the super class
  if ( !Layer::init() )
  {
      return false;
  }

  // Initialize the text layer
  this->text = cocos2d::Label::createWithTTF(fa_icon(icon), Q_ICON_PATH, size);
  this->addChild(this->text);

  return true;
}

IconNode::IconNode(const char16_t * icon, float size) {
  this->icon = icon;
  this->size = size;
}

}
