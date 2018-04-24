#ifndef __CDS_ENEMY_TRACKER_SHOOT_H
#define __CDS_ENEMY_TRACKER_SHOOT_H

#include "Enemy_Tracker.h"
#include "enemy_missile.h"
#include "world.h"
#include "image_sequence.h"

namespace csis3700 {

	class Enemy_Tracker;
	class world;
	class Enemy_Tracker_Shoot : public Enemy_Tracker
	{
	public:
		Enemy_Tracker_Shoot(world* w, float initialX = 0, float initialY = 0);
		~Enemy_Tracker_Shoot();

		// Inherited via Enemy_Sprite
		virtual void resolve(const collision & collision, sprite * other);
		virtual void advance_by_time(double dt);
	private:
		float fireRate;
		float lastFireTime;
		void Fire();
		void create_image_sequence();

	};
}

#endif
