#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Constants.h"
#include "States.h"

#include "MenuButtonLayer.h"
#include "CloseButton.h"

#include "BackgroundLayer.h"
#include "menu/MenuLayer.h"
#include "defs/DefinitionLayer.h"
#include "solver/PuzzleLayer.h"
#include "ads/AdLayer.h"

#include "models/Game.h"


namespace QUAT {

// The state controller needs to be predefined
class GameStateController;

class GameScene : public cocos2d::Layer
{

private:
    // The game's full model
    Game * game;

    // Holds information about the game state
    GameStateController * GSC;

    // The colorful global background of the game.
    BackgroundLayer * background;

    // Layer for actually playing the game
    PuzzleLayer * puzzleLayer;

    DefinitionLayer * definitionLayer;

    // Layer for actually playing the game
    MenuLayer * menuLayer;

    AdLayer * adLayer;

    // Stores the boundaries of the game
    cocos2d::Rect * gameBounds;

    // Menu button that the user can press to reach the "menu", an about screen
    // with statistics and other information about the game.
    MenuButtonLayer * menuButton;

    CloseButton * closeButton;

    /**
     * Generates the bounds of the game used to render everything.
     * @return Rect representing the game area.
     */
    void generateBounds();

    void menuCallback();

    /*
     * Does all the showing and hiding
     * necessary to fulfill a state transition.
     */
    void showLayer(GAME_STATE state);

public:

    // Transitions the user interface to a new state.
    void toState(GAME_STATE state);
    
    // Functions that get called when the app enters the background
    // and foreground.
    void enteredBackground();
    void enteredForeground();

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
    
    void update(float delta) override;
};

}
#endif // __GAME_SCENE_H__
