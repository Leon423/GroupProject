#ifndef __CDS_PICKUP_H
#define __CDS_PICKUP_H
#include "sprite.h"

namespace csis3700 {

	class pickup : public sprite
	{
	public:
		pickup(float initX, float initY);
		~pickup();

	};
}

#endif
