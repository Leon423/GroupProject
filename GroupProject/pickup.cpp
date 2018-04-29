#include "stdafx.h"
#include "pickup.h"
#include "vec2d.h"
#include "image_sequence.h"
#include "image_library.h"

namespace csis3700 {

	pickup::pickup(float initX, float initY) : sprite(initX, initX)
	{
		collisionChan = Collectible;
		set_position(vec2d(initX, initY));
	}

	pickup::~pickup()
	{
	}

}
