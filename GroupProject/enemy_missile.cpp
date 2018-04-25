#include "stdafx.h"
#include "enemy_missile.h"
#include "image_library.h"
#include "image_sequence.h"
#include "Enemy_Sprite.h"
#include "world.h"

namespace csis3700 {
	enemy_missile::enemy_missile(world* w , float initial_x, float initial_y) : phys_sprite(initial_x, initial_y)
	{
		lifeSpan = 2.0;
		theWorld = w;
		//set_position(vec2d(initial_x, initial_y));
		creationTime = time;
		speed = -100;
		set_velocity(vec2d(speed, 0));
		collisionChan = Enemy;
		explodeNextFrame = false;
		//isDead = false;
		create_image_sequence();
	}

	void enemy_missile::create_image_sequence()
	{
		defaultSequence = new image_sequence();
		image_library *lib = image_library::get();
		defaultSequence->add_image(lib->get("blah.jpg"), 0);
		set_image_sequence(defaultSequence);
	}

	enemy_missile::~enemy_missile()
	{
		delete defaultSequence;

		
	}
	void enemy_missile::advance_by_time(double dt)
	{
		if ((time - creationTime) >= lifeSpan || explodeNextFrame)
			Explode();
		else
			phys_sprite::advance_by_time(dt);
	}
	void enemy_missile::resolve(const collision & collision, sprite * other)
	{
		// should never get called
	}
	void enemy_missile::Explode()
	{
		//theWorld->removeSprite(this);
		isDead = true;
	}

	void enemy_missile::collidedWithPlayer()
	{
		explodeNextFrame = true;
	}

}