
#include "GameStateController.h"
#include "GameScene.h"

namespace QUAT {


void GameStateController::setState(GameStateController::STATE newState) {
	// Set the last state
	this->_lastState = this->_state;

	// Change the current state
	this->_state = newState;
}

void GameStateController::to_GAME() {
	this->gameScene->to_GAME();
	this->setState(GAME);
}

void GameStateController::to_INFO() {
	this->gameScene->to_INFO();
	this->setState(INFO);
}

void GameStateController::to_AD() {
	this->gameScene->to_AD();
	this->setState(INFO);
}

void GameStateController::to_GAME_DEFS() {
	this->gameScene->to_GAME_DEFS();
	this->setState(GAME_DEFS);
}

void GameStateController::to_WB_DEFS() {
	this->gameScene->to_WB_DEFS();
	this->setState(WB_DEFS);
}


GameStateController::STATE GameStateController::state() {
	return this->_state;
}

GameStateController::GameStateController(GameScene * gameScene) {
	this->gameScene = gameScene;

	this->_state = GAME;
	this->setState(GAME);
}

}
