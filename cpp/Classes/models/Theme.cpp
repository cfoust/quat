#include "Theme.h"
#include "Game.h"

namespace QUAT {
ColorScheme Theme::getColorScheme() {
	return this->scheme;
}

bool Theme::getColorSchemeChanged() {
	return this->colorSchemeChanged;
}

void Theme::update(Game * model) {

}

Theme::Theme() {
	this->colorSchemeChanged = false;
	this->scheme.top = cocos2d::Color3B(240,48,179);
	this->scheme.bottom = cocos2d::Color3B(82,88,254);
}

};