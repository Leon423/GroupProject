#ifndef __CDS_Enemy_MISSILE_H
#define __CDS_Enemy_MISSILE_H
#include "phys_sprite.h"
#include "Enemy_Sprite.h"
#include "image_sequence.h"
#include "world.h"


namespace csis3700 {

	class world;
	class image_sequence;

	class enemy_missile : public phys_sprite {
	public:
		enemy_missile(world* p, float initial_x = 0, float initial_y = 0);
		~enemy_missile();
		virtual void advance_by_time(double dt);

		bool is_player()
		{
			return false;
		}

		virtual void resolve(const collision& collision, sprite* other);

		void Explode();

		void collidedWithPlayer();

	private:
		// pointer to the world
		world * theWorld;
		void create_image_sequence();
		// the default animation that plays
		image_sequence *defaultSequence;
		// animation for the barrel roll
		image_sequence *explodeImageSequence;
		double lifeSpan;
		double speed;
		double creationTime;
		bool explodeNextFrame;
	};
}


#endif /* PLAYER_SPRITE_H */
