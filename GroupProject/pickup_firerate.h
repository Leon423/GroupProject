#ifndef __CDS_PICKUP_FIRERATE_H
#define __CDS_PICKUP_FIRERATE_H

#include "pickup.h"
#include "player_sprite.h"

namespace csis3700 {

	class player_sprite;
	class pickup;

	class pickup_firerate : public pickup
	{
	public:
		pickup_firerate(float initX =0, float initY =0);
		~pickup_firerate();
		virtual void OnPickup(player_sprite * p);

		

	private:
		double firerateIncrease;
		virtual void create_image_sequence();
	};
}
#endif
