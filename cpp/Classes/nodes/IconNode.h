#ifndef __STAR_NODE_H__
#define __STAR_NODE_H__

#include "cocos2d.h"
#include "../Constants.h"
#include "../Utils.h"
#include <string>

namespace QUAT {

USING_NS_CC;
using namespace std;

class IconNode : public cocos2d::Layer
{
private:
  const char16_t * icon;

  float size;

	Label * text;

public:
	/**
	 * Creates and returns a IconNode.
	 */
	static IconNode * create(const char16_t * icon, float size);
	
	bool init();
	
	IconNode(const char16_t * icon, float size);

  Label * getLabel();
};

}

#endif // __STAR_NODE_H__
