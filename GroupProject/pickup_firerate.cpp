#include "stdafx.h"
#include "pickup_firerate.h"
#include "pickup.h"
#include "player_sprite.h"
#include "image_library.h"
#include "image_sequence.h"

namespace csis3700 {
	pickup_firerate::pickup_firerate(float initX, float initY) : pickup(initX, initY)
	{
		firerateIncrease = 1;
		create_image_sequence();
	}


	pickup_firerate::~pickup_firerate()
	{
	}
	void pickup_firerate::OnPickup(player_sprite* p)
	{
		p->IncreaseFireRate(firerateIncrease);
		isDead = true;
	}
	void pickup_firerate::create_image_sequence()
	{
		image_sequence* s = new image_sequence();
		image_library* lib = image_library::get();

		s->add_image(lib->get("PY1.jpg"), .2);
		s->add_image(lib->get("PY2.jpg"), .2);
		s->add_image(lib->get("PY3.jpg"), .2);
		s->add_image(lib->get("PY4.jpg"), .2);
		s->add_image(lib->get("PY5.jpg"), .2);
		s->add_image(lib->get("PY6.jpg"), .2);

		set_image_sequence(s);
	}
}