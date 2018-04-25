#ifndef __CDS_PICKUP_H
#define __CDS_PICKUP_H
#include "sprite.h"
#include "player_sprite.h"
namespace csis3700 {

	class player_sprite;

	class pickup : public sprite
	{
	public:
		pickup(float initX= 0, float initY= 0);
		~pickup();

		virtual void OnPickup(player_sprite* p) =0;

	};
}

#endif
