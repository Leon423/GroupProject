#ifndef __CDS_PICKUP_H
#define __CDS_PICKUP_H
#include "sprite.h"
#include "player_sprite.h"
#include "vec2d.h"
#include "collision.h"

namespace csis3700 {

	class player_sprite;

	class pickup : public sprite
	{
	public:
		pickup(float initX= 0, float initY= 0);
		~pickup();

		virtual void OnPickup(player_sprite* p) =0;

		virtual vec2d get_velocity() const
		{
			// do nothing
			return vec2d(0, 0);
		}

		virtual void set_velocity(const vec2d& v)
		{
			// do nothing we don't move
		}

		virtual void resolve(const collision& collision, sprite* other)
		{
			// do nothing
		}

	private:
		virtual void create_image_sequence() =0;
	};
}

#endif
