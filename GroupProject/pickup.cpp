#include "stdafx.h"
#include "pickup.h"
#include "vec2d.h"

namespace csis3700 {

	pickup::pickup(float initX, float initY) : sprite(initX, initX)
	{
		collisionChan = Collectible;
	}

	pickup::~pickup()
	{
	}
}
