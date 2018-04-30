#include "stdafx.h"
#include "Pickup_Coin.h"
#include "pickup.h"
#include "player_sprite.h"
#include "image_library.h"
#include "image_sequence.h"

namespace csis3700 {

	Pickup_Coin::Pickup_Coin(float initX, float initY) : pickup(initX, initY)
	{
		scoreIncrease = 5;
		create_image_sequence();
	}


	Pickup_Coin::~Pickup_Coin()
	{
	}
	void Pickup_Coin::OnPickup(player_sprite * p)
	{
		p->AddScore(scoreIncrease);
		isDead = true;
	}
	void Pickup_Coin::create_image_sequence()
	{
		image_sequence* s = new image_sequence();
		image_library* lib = image_library::get();

		s->add_image(lib->get("GC0.png"), .2);
		s->add_image(lib->get("GC1.png"), .2);
		s->add_image(lib->get("GC2.png"), .2);
		s->add_image(lib->get("GC3.png"), .2);
		s->add_image(lib->get("GC4.png"), .2);
		s->add_image(lib->get("GC5.png"), .2);
		s->add_image(lib->get("GC6.png"), .2);

		set_image_sequence(s);
	}
}
