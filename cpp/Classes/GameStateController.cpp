
#include "GameStateController.h"
#include "GameScene.h"

namespace QUAT {


void GameStateController::setState(GAME_STATE newState) {
	// Set the last state
	this->_lastState = this->_state;

  // Run the callback for the from state
  this->gameScene->fromState(this->_state);

	// Change the current state
	this->_state = newState;

  // Update the UI to match the new state
  this->gameScene->toState(newState);
}

GAME_STATE GameStateController::state() {
	return this->_state;
}

GameStateController::GameStateController(GameScene * gameScene) {
	this->gameScene = gameScene;

	this->_state = S_PuzzleSolver;
}

}
