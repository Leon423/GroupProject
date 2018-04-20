#include "stdafx.h"

#include "player_sprite.h"
#include "image_library.h"
#include "image_sequence.h"
#include "vec2d.h"
#include "collision.h"
#include <cmath>
#include "world.h";
#include "keyboard_manager.h"
using namespace std;

namespace csis3700 {

  player_sprite::player_sprite(world* w, float initial_x, float initial_y) : 
    phys_sprite(initial_x, initial_y) {

	  theWorld = w;
	  create_image_sequence();

  }

  void player_sprite::create_image_sequence()
  {
	  image_sequence *s = new image_sequence();
	  image_library *lib = image_library::get();
	  s->add_image(lib->get("blah.jpg"), 0);
	  s->add_image(lib->get("blah2.jpg"), 0.2);
	  s->add_image(lib->get("blah.jpg"), 0.2);
	  set_image_sequence(s);
  }

  void player_sprite::advance_by_time(double dt) {
	  
	  if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_LEFT))
		  set_velocity(vec2d(-100, 0));
	  else if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_RIGHT))
		  set_velocity(vec2d(100, 0));
	  else if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_UP))
		  set_velocity(vec2d(0, -50));
	  else if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_DOWN))
		  set_velocity(vec2d(0, 50));
	  else
		  set_velocity(vec2d(0, 0));
	  phys_sprite::advance_by_time(dt);
  }

  void player_sprite::resolve(const collision& collision, sprite* other)
  {
	  // for now we just tell the world we died
	  theWorld->player_killed();
  }

}
