#ifndef __CDS_ENEMY_FLYER_H
#define __CDS_ENEMY_FLYER_H

#include "Enemy_Sprite.h"
#include "world.h"

namespace csis3700 {

	class Enemy_Sprite;
	class world;

	class Enemy_Flyer : public Enemy_Sprite
	{
	public:
		Enemy_Flyer(world* w, float initialX = 0, float initialY = 0);
		~Enemy_Flyer();

		void create_image_sequence();

		// Inherited via Enemy_Sprite
		virtual void resolve(const collision & collision, sprite * other);
		virtual void advance_by_time(double dt);
	};
}

#endif

