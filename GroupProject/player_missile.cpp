#include "stdafx.h"
#include "player_missile.h"
#include "phys_sprite.h"
#include "player_sprite.h"
#include "image_library.h"
#include "enemy_missile.h"
#include "Enemy_Sprite.h"

namespace csis3700
{
	player_missile::~player_missile()
	{
		//destructor
		delete defaultSequence;
	}

	csis3700::player_missile::player_missile(player_sprite * p, float initial_x, float initial_y) : phys_sprite(initial_x, initial_y)
	{
		lifeSpan = 7;
		owner = p;
		//set_position(vec2d(initial_x, initial_y));
		speed = 300;
		set_velocity(vec2d(speed, 0));
		creationTime = time;
		pointsScored = 0;
		collisionChan = PlayerMissile;
		explodeNextFrame = false;
		create_image_sequence();
	}

	void csis3700::player_missile::advance_by_time(double dt)
	{
		if ((time - creationTime) >= lifeSpan || explodeNextFrame)
		{
			Explode();
		}
		phys_sprite::advance_by_time(dt);
	}

	void csis3700::player_missile::resolve(const collision & collision, sprite * other)
	{
		/*TODO: Update collision responses to handle missiles so we can blow them up!*/
		if (other->GetCollisionChannel() == Enemy)
		{
			// we destroy the baddie!
			Enemy_Sprite *s = dynamic_cast<Enemy_Sprite*>(other);
			if (s != NULL)
			{
				pointsScored += s->GetPoints();
				s->die();
				// should probably set explosion image sequence at this point?
				explodeNextFrame = true;

				return;
			}
		}

		if (other->GetCollisionChannel() == Collectible)
		{
			// do we need to do anything?
		}

		if (other->GetCollisionChannel() == Player)
		{
			printf("WOOOOOOOO");
		}


	}

	void player_missile::create_image_sequence()
	{
		/*TODO: UPDATE GRAPHICS!!!! ALSO NEED EXPLOSION GRAPHIC!*/
		defaultSequence = new image_sequence();
		
		image_library *lib = image_library::get();
		defaultSequence->add_image(lib->get("blah.jpg"), 0);
		set_image_sequence(defaultSequence);
	}

	void player_missile::Explode()
	{
		/*TODO: PLAY EXPLOSION*/
		isDead = true;
		owner->RemoveMissile(this);
	}
}