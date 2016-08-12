#ifndef __GAME_STATE_CONTROLLER_H__
#define __GAME_STATE_CONTROLLER_H__

namespace QUAT {
// Pre-define GameScene because it depends on this too
class GameScene;


class GameStateController
{
public:
	enum STATE {
		GAME,
		INFO,
		GAME_DEFS,
		WB_DEFS
	};

private:
	GameScene * gameScene;

	STATE _state,
		  _lastState;

	void setState(STATE newState);

public:

	void to_GAME();

	void to_INFO();

	void to_GAME_DEFS();

	void to_WB_DEFS();

	/**
	 * Gets the current state.
	 */
	STATE state();

	/**
	 * @brief      Gets the last state.
	 *
	 * @return     Gets the previous state.
	 */
	STATE lastState();

	GameStateController(GameScene * gameScene);


};

}

#endif // __GAME_STATE_CONTROLLER_H__
