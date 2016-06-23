#include "BackgroundLayer.h"

USING_NS_CC;

namespace QUAT {

BackgroundLayer::BackgroundLayer()
{   
	// Adds a simple background layer, for now this gradient is hard-coded
    auto bg = LayerGradient::create(Color4B(240,48,179,255), Color4B(82,88,254,255));
    addChild(bg, 0);
}

}