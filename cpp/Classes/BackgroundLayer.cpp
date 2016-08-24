#include "BackgroundLayer.h"

USING_NS_CC;

namespace QUAT {


void BackgroundLayer::setScheme(ColorScheme scheme) {
	this->gradient->setStartColor(scheme.top);
	this->gradient->setEndColor(scheme.bottom);
}

void BackgroundLayer::animateScheme(ColorScheme scheme) {
	this->setScheme(scheme);
}

bool BackgroundLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }
    
	// Adds a simple background layer, for now this gradient is hard-coded
    this->gradient = LayerGradient::create(Color4B(240,48,179,255), Color4B(82,88,254,255));
    addChild(this->gradient, 0);

    return true;
}

}