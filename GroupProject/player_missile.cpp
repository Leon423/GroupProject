#include "stdafx.h"
#include "player_missile.h"
#include "phys_sprite.h"
#include "player_sprite.h"
#include "image_library.h"
namespace csis3700
{
	player_missile::~player_missile()
	{
		//destructor
	}

	csis3700::player_missile::player_missile(player_sprite * p, float initial_x, float initial_y)
	{
		lifeSpan = 4.0;
		owner = p;
		set_position(vec2d(initial_x, initial_y));
		speed = 300;
		set_velocity(vec2d(speed, 0));
		creationTime = time;
		pointsScored = 0;
		create_image_sequence();
	}

	void csis3700::player_missile::advance_by_time(double dt)
	{
		if ((time - creationTime) >= lifeSpan)
		{
			Explode();
		}
		phys_sprite::advance_by_time(dt);
	}

	void csis3700::player_missile::resolve(const collision & collision, sprite * other)
	{
		/*TODO: Update collision responses to handle missiles so we can blow them up!*/

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

		owner->RemoveMissile(this);
	}
}