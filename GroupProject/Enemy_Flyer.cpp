#include "stdafx.h"
#include "Enemy_Flyer.h"
#include "Enemy_Sprite.h"
#include "vec2d.h"
#include "world.h"
#include "image_library.h"
#include "image_sequence.h"

namespace csis3700 {
	
	Enemy_Flyer::Enemy_Flyer(world * w, float initialX, float initialY) : Enemy_Sprite(w, initialX, initialY)
	{
		theWorld = w;
		set_position(vec2d(initialX, initialY));
		speedY = 0; // these just fly straight so no Y speed
		speedX = 100;
		collisionChan = Enemy;
		set_velocity(vec2d(speedX, speedY));
		create_image_sequence();
	}
	Enemy_Flyer::~Enemy_Flyer()
	{
	}

	void Enemy_Flyer::create_image_sequence()
	{
		defaultSequence = new image_sequence();
		image_library *lib = image_library::get();
		defaultSequence->add_image(lib->get("enemy5.png"), 0.1);
		defaultSequence->add_image(lib->get("enemy5_1.png"), 0.1);
		defaultSequence->add_image(lib->get("enemy5_2.png"), 0.1);
		defaultSequence->add_image(lib->get("enemy5_1.png"), 0.1);
		set_image_sequence(defaultSequence);
	}

	void csis3700::Enemy_Flyer::resolve(const collision & collision, sprite * other)
	{
		// this should never get called
	}

	void csis3700::Enemy_Flyer::advance_by_time(double dt)
	{
		phys_sprite::advance_by_time(dt);
	}
}