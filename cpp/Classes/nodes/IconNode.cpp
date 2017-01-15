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

Texture2D * IconNode::toTexture() {
  auto renderer = Director::getInstance()->getRenderer();
  Mat4 parentTransform = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

  // Move the text in local space
  this->text->setPosition(size / 2, size / 2);

  // Visit the text label
  this->render->beginWithClear(0,0,0,0);
  this->text->visit(renderer, parentTransform, true);
  this->render->end();

  // Move it back to its original position
  this->text->setPosition(0, 0);

  return this->render->getSprite()->getTexture();
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

  // Set up the render target so the user can get this sprite's texture
  this->render = RenderTexture::create(size, size, Texture2D::PixelFormat::RGBA8888);
  this->render->setPosition(-1 * size, -1 * size);
  //this->addChild(this->render);

  return true;
}

IconNode::IconNode(const char16_t * icon, float size) {
  this->icon = icon;
  this->size = size;
}

}
