#ifndef __BORDERED_WORD_NODE_H__
#define __BORDERED_WORD_NODE_H__

#include "cocos2d.h"

#include "WordNode.h"
#include "../nodes/RectRadius.h"

namespace QUAT {

class BorderedWordNode : public WordNode
{
private:
	// Holds the borders of the letters
	RectRadius * borders[4];

	// Holds the fills of the letters
	RectRadius * fills[4];

	// The default and selected colors for the borders
	cocos2d::Color4B * defaultColor,
					 * selectedColor;


public:
	bool init();

	void select(int column);

	void unselect();
	
	BorderedWordNode(float fontSize, float fontGap);
	
	static BorderedWordNode * create(float fontSize, float fontGap);
};

}

#endif // __BORDERED_WORD_NODE_H__
