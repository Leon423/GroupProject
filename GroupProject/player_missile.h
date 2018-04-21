#ifndef __CDS_PLAYER_Missile_H
#define __CDS_PLAYER_Missile_H
#include "phys_sprite.h"
#include "player_sprite.h"
#include "image_sequence.h"

namespace csis3700 {

	class world;
	class image_sequence;
	class player_sprite;

	class player_missile : public phys_sprite {
	public:
		player_missile(player_sprite* p, float initial_x = 0, float initial_y = 0);
		~player_missile();
		virtual void advance_by_time(double dt);

		bool is_player()
		{
			return false;
		}

		virtual void resolve(const collision& collision, sprite* other);

		void Explode();

		double get_points()
		{
			return pointsScored;
		}

	private:
		// pointer to the world
		player_sprite *owner;
		void create_image_sequence();
		// the default animation that plays
		image_sequence *defaultSequence;
		// animation for the barrel roll
		image_sequence *explodeImageSequence;
		double lifeSpan;
		double speed;
		double creationTime;
		double pointsScored;
	};
}


#endif /* PLAYER_SPRITE_H */
