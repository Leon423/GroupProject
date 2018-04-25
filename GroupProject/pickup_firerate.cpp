#include "stdafx.h"
#include "pickup_firerate.h"
#include "pickup.h"
#include "player_sprite.h"

namespace csis3700 {
	pickup_firerate::pickup_firerate(float initX, float initY) : pickup(initX, initY)
	{
		firerateIncrease = 1;
	}


	pickup_firerate::~pickup_firerate()
	{
	}
	void pickup_firerate::OnPickup(player_sprite* p)
	{
		p->IncreaseFireRate(firerateIncrease);
		isDead = true;
	}
}