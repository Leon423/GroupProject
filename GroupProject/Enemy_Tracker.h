#ifndef __CDS_ENEMY_TRACKER_H
#define __CDS_ENEMY_TRACKER_H

#include "Enemy_Sprite.h"
#include "world.h"
#include "sprite.h"

namespace csis3700 {

	class Enemy_Sprite;
	class world;
	class sprite;

	class Enemy_Tracker : public Enemy_Sprite
	{
	public:
		Enemy_Tracker(world* w, float initialX = 0, float initialY = 0);
		~Enemy_Tracker();

		void create_image_sequence();

		// Inherited via Enemy_Sprite
		virtual void resolve(const collision & collision, sprite * other);
		virtual void advance_by_time(double dt);

	private:
		const sprite * target;
		bool targetLocked;
	};
}

#endif

