#include "stdafx.h"

#include "world.h"
#include <cassert>
#include <algorithm>
#include "sprite.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "player_sprite.h"
#include "obstruction_sprite.h"
#include "collision.h"
#include "image_library.h"

using namespace std;

namespace csis3700 {

  const float gravity_acceleration = 600;

  void free_sprite(sprite* s) {
    delete s;
  }

  world::world() {
	  image_library *lib = image_library::get();

	  background = lib->get("Background.jpg");

	  create_sprites();
  }

  void world::create_sprites()
  {
	  player = new player_sprite(this, 0, 0);
	  sprites.push_back(player);
  }

  world::world(const world& other) {
    assert(false); // do not copy worlds
  }

  world& world::operator=(const world& other) {
    assert(false); // do not assign worlds

	// done to appease compiler
	world w = world();

	return w;
  }

  world::~world() {
    for_each(sprites.begin(), sprites.end(), free_sprite);
    sprites.clear();
  }

  void world::handle_event(ALLEGRO_EVENT ev) {
  }

  void world::resolve_collisions() {

	  vector<collision> collisions;
	  for (auto i = sprites.begin(); i != sprites.end(); ++i)
	  {
		  for (auto j = i+1; j != sprites.end(); j++)
		  {
			  if ((*i)->collides_with(**j))
				  collisions.push_back(collision(*i, *j));
		  }
	  }

	  handle_collisions(collisions);

  }

  void world::handle_collisions(vector<collision>& collisions)
  {
	  for (auto it = collisions.begin(); it != collisions.end(); ++it)
	  {
		  it->resolve();
	  }
  }

  void world::advance_by_time(double dt) {
    for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
      (*it)->advance_by_time(dt);
    resolve_collisions();
  }

  void world::draw() {
    al_clear_to_color(al_map_rgb(255,255,255));

	al_draw_bitmap(background, 0, 0, 0);

    for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
      (*it)->draw();
  }

  bool world::should_exit() {
    return false;
  }

  void world::player_killed()
  {
	  if (sprites.front()->is_player())
		  sprites.erase(sprites.begin());
  }

}
