
#include "SolverStateController.h"
#include "PuzzleLayer.h"

namespace QUAT {


void SolverStateController::setState(SolverStateController::STATE newState) {
	this->_state = newState;
}
void SolverStateController::to_IDLE() {
	this->puzzleLayer->goIdle();
	this->setState(IDLE);
}
void SolverStateController::to_CHOOSING_LETTER(int column) {
	this->puzzleLayer->chooseLetter(column);
	this->setState(CHOOSING_LETTER);
}
SolverStateController::STATE SolverStateController::state() {
	return this->_state;
}

SolverStateController::SolverStateController(PuzzleLayer * puzzleLayer) {
	this->puzzleLayer = puzzleLayer;
	this->setState(IDLE);
}

}
