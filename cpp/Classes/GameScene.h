#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"

namespace QUAT {

class GameScene : public cocos2d::Layer
{
private:
	BackgroundLayer * background;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(GameScene);
};

}
#endif // __GAME_SCENE_H__
