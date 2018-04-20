#include "stdafx.h"

#include "collision.h"
#include "rectangle.h"
#include <iostream>
using namespace std;

namespace csis3700 {
  collision::collision(sprite* p1, sprite* p2) {
	  if (!p1->is_player())
	  {
		  participants[0] = p2;
		  participants[1] = p1;
	  }
	  else
	  {
		  participants[0] = p1;
		  participants[1] = p2;
	  }
  }

  sprite** collision::get_participants()  { return participants; }

  rectangle collision::collision_rectangle() const {
    return participants[0]->collision_rectangle(*participants[1]);
  }

  void collision::resolve()
  {
	  if (!participants[0]->is_player()) return; //if player isnt involved we dont care
	  // will probably change at some point

	  participants[0]->resolve(*this, participants[1]);
  }

}
