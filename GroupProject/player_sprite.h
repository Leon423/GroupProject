#ifndef __CDS_PLAYER_SPRITE_H
#define __CDS_PLAYER_SPRITE_H
#include "phys_sprite.h"
#include "world.h"

namespace csis3700 {

	class world;

  class player_sprite : public phys_sprite {
  public:
    player_sprite(world* w, float initial_x=0, float initial_y=0);
    virtual void advance_by_time(double dt);

	bool is_player()
	{
		return true;
	}

	virtual void resolve(const collision& collision, sprite* other);

  private:
	  world *theWorld;
	  void create_image_sequence();
  };
}


#endif /* PLAYER_SPRITE_H */
