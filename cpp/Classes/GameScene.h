#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"

namespace QUAT {

class GameScene : public cocos2d::Layer
{

private:
	// The colorful global background of the game.
	BackgroundLayer * background;

public:
	/**
	 * Creates a scene object with a game scene that is used by the director 
	 * for rendering.
	 * @return Pointer to created scene object.
	 */
    static cocos2d::Scene* createScene();

    /**
     * Initializes the game scene. Called by the create function.
     * @return bool: whether or not the init was successful.
     */
    virtual bool init();

    /**
     * Syntactic sugar for cocos2dx's object creation scheme.
     */
    CREATE_FUNC(GameScene);
};

}
#endif // __GAME_SCENE_H__
