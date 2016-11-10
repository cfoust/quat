#ifndef __GAME_STATE_CONTROLLER_H__
#define __GAME_STATE_CONTROLLER_H__

#include "States.h"

namespace QUAT {

// Pre-define GameScene because it depends on this too
class GameScene;

class GameStateController
{
public:

private:
	GameScene * gameScene;

	GAME_STATE _state,
		        _lastState;
public:
	void setState(GAME_STATE newState);

	/**
	 * Gets the current state.
	 */
	GAME_STATE state();

	/**
	 * @brief      Gets the last state.
	 *
	 * @return     Gets the previous state.
	 */
  GAME_STATE lastState();

	GameStateController(GameScene * gameScene);
};

}

#endif // __GAME_STATE_CONTROLLER_H__
