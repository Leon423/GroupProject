#include "stdafx.h"
#include "Enemy_Tracker_Shoot.h"
#include "Enemy_Tracker.h"
#include "enemy_missile.h"
#include "image_sequence.h"
#include "image_library.h"
#include "pickup.h"
#include "pickup_firerate.h"

namespace csis3700 {
	Enemy_Tracker_Shoot::Enemy_Tracker_Shoot(world * w, float initialX, float initialY) : Enemy_Tracker(w, initialX, initialY)
	{
		fireRate = 1;
		lastFireTime = 0;
		speedX = 100;
		speedY = 0;
		set_velocity(vec2d(speedX, speedY));
		create_image_sequence();
	}
	Enemy_Tracker_Shoot::~Enemy_Tracker_Shoot()
	{
		Enemy_Tracker::~Enemy_Tracker();

	}

	void Enemy_Tracker_Shoot::create_image_sequence()
	{
		defaultSequence = new image_sequence();
		image_library *lib = image_library::get();
		defaultSequence->add_image(lib->get("enemy1.png"), 0.1);
		defaultSequence->add_image(lib->get("enemy1_1.png"), 0.2);
		defaultSequence->add_image(lib->get("enemy1_2.png"), 0.2);
		defaultSequence->add_image(lib->get("enemy1_1.png"), 0.2);
		set_image_sequence(defaultSequence);


	}

	void Enemy_Tracker_Shoot::resolve(const collision & collision, sprite * other)
	{
		// should never get called
	}
	void Enemy_Tracker_Shoot::advance_by_time(double dt)
	{

		//updates position, which we need to do before firing
		Enemy_Tracker::advance_by_time(dt);

		if ((time - lastFireTime) >= fireRate)
		{
			Fire();
		}

		CheckBounds();
	}

	void Enemy_Tracker_Shoot::SpawnPickup()
	{
		if (theWorld->shouldSpawnPickup())
		{
			float spawnX = get_x() + defaultSequence->get_width() / 2;
			float spawnY = get_y() + defaultSequence->get_height() / 2;

			pickup_firerate* p = new pickup_firerate(spawnX, spawnY);
			theWorld->addSprite(p);
		}
	}

	void Enemy_Tracker_Shoot::Fire()
	{
		lastFireTime = time;
		theWorld->addMissile(new enemy_missile(theWorld, get_x() - 20, get_y()));
	}
}