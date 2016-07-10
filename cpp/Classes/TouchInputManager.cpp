#include "TouchInputManager.h"

namespace QUAT {

TouchInputManager::TouchInputManager() {
	this->lastDown = new cocos2d::Vec2(0,0);
}

void TouchInputManager::setEnabled(bool enabled) {
	this->enabled = enabled;
}

bool TouchInputManager::getEnabled() {
	return this->enabled;
}

void TouchInputManager::inputBegan(cocos2d::Vec2 * point) {
	if (!this->enabled) {
		return;
	}

	this->lastDown = point;
	this->began(point);
}

void TouchInputManager::inputMoved(cocos2d::Vec2 * point) {
	if (!this->enabled) {
		return;
	}

	this->moved(point);
}

void TouchInputManager::inputDone(cocos2d::Vec2 * point) {
	if (!this->enabled) {
		return;
	}

	this->done(point);
}

}