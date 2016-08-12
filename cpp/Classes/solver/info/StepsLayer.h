#ifndef __STEPS_LAYER_H__
#define __STEPS_LAYER_H__

#include "cocos2d.h"
#include "../../Constants.h"

#include "../input/WordNode.h"

namespace QUAT {

class StepsLayer : public cocos2d::Layer
{
private:
	std::vector<WordNode*> * nodes;

	float fontSize;
public:

	void update(std::vector<std::string> * steps);

	void setOpacity(GLubyte opacity);
	
	bool init();

	StepsLayer(float fontSize);
	
	static StepsLayer * create(float fontSize);

};

}

#endif // __STEPS_LAYER_H__
