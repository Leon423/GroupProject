#ifndef __CDS_PICKUP_COIN_H
#define __CDS_PICKUP_COIN_H

#include "pickup.h"
#include "player_sprite.h"

namespace csis3700 {

	class player_sprite;
	class pickup;

	class Pickup_Coin : public pickup
	{
	public:
		Pickup_Coin(float initX = 0, float initY = 0);
		~Pickup_Coin();
		virtual void OnPickup(player_sprite * p);



	private:
		double scoreIncrease;
		virtual void create_image_sequence();
	};
}
#endif
