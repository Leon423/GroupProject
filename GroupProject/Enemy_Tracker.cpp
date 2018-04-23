#include "stdafx.h"
#include "Enemy_Tracker.h"
#include "world.h"
#include "vec2d.h"
#include "sprite.h"
#include "image_library.h"
#include "image_sequence.h"
#include "phys_sprite.h"

namespace csis3700 {

	Enemy_Tracker::Enemy_Tracker(world * w, float initialX, float initialY)
	{
		theWorld = w;
		set_position(vec2d(initialX, initialY));
		speedX = 100;
		speedY = 0;
		collisionChan = Enemy;
		target = theWorld->get_player();
		targetLocked = false;
		set_velocity(vec2d(speedX, speedY));
		create_image_sequence();
	}
	Enemy_Tracker::~Enemy_Tracker()
	{
	}
	void Enemy_Tracker::create_image_sequence()
	{
		defaultSequence = new image_sequence();
		image_library *lib = image_library::get();
		defaultSequence->add_image(lib->get("blah2.jpg"), 0);
		set_image_sequence(defaultSequence);
	}
	void Enemy_Tracker::resolve(const collision & collision, sprite * other)
	{
		// this should never get called currently
	}
	void Enemy_Tracker::advance_by_time(double dt)
	{
		double targetY = target->get_y();

		if (targetY > get_y())
		{
			// below us so go down
			speedY = 100;
		}
		else if (targetY < get_y())
		{
			//above us to go up
			speedY = -100;
		}

		set_velocity(vec2d(speedX, speedY));

		phys_sprite::advance_by_time(dt);
	}
}