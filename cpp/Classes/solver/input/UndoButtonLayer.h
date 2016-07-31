#ifndef __UNDO_LAYER_H__
#define __UNDO_LAYER_H__

#include "cocos2d.h"
#include "../../Clickable.h"

namespace QUAT {

class UndoButtonLayer : public Clickable
{
private:
	cocos2d::Sprite * background;

	float size;

	void up();
	void entered();
	void left();
public:
	bool init();
	
	UndoButtonLayer(float size);
	
	static UndoButtonLayer * create(float size);

};

}

#endif // __UNDO_LAYER_H__
