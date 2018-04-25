#include "stdafx.h"

#include "collision.h"
#include "rectangle.h"
#include <iostream>
using namespace std;

namespace csis3700 {
  collision::collision(sprite* p1, sprite* p2) {
	  //check if either is player
	  if (p1->is_player())
	  {
		  participants[0] = p1;
		  participants[1] = p2;
	  }
	  else if (p2->is_player())
	  {
		  participants[0] = p2;
		  participants[1] = p1;
	  }
	  else if (p1->GetCollisionChannel() == sprite::PlayerMissile)
	  {
		  participants[0] = p1;
		  participants[1] = p2;
	  }
	  else
	  {
		  participants[0] = p2;
		  participants[1] = p1;
	  }

  }

  sprite** collision::get_participants()  { return participants; }

  rectangle collision::collision_rectangle() const {
    return participants[0]->collision_rectangle(*participants[1]);
  }

  void collision::resolve()
  {
	  // Player, or his missiles, not involved so we don't care.
	  if (!participants[0]->is_player() && !(participants[0]->GetCollisionChannel() == sprite::PlayerMissile))
		  return;
	  //if this is a collision between a player and his missile then we dont care
	  if ((participants[0]->is_player() && (participants[1]->GetCollisionChannel() == sprite::PlayerMissile)) 
		  || (participants[1]->is_player() && (participants[0]->GetCollisionChannel() == sprite::PlayerMissile)))
	  {
		  return;
	  }
		  
	  participants[0]->resolve(*this, participants[1]);
  }

}
