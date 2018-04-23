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
#include <algorithm>
#include "allegro5/allegro_font.h"

using namespace std;

namespace csis3700 {

  const float gravity_acceleration = 600;

  void free_sprite(sprite* s) {
    delete s;
  }

  world::world() {
	  image_library *lib = image_library::get();

	  background = lib->get("Background.jpg");
	  lastSpawnTime = 0;
	  time = 0;
	  create_sprites();
  }

  void world::create_sprites()
  {
	  player = new player_sprite(this, 0, 0);
	  sprites.push_back(player);
  }

  void world::addSprite(sprite *s)
  {
	  spritesToAdd.push_back(s);
  }

  void world::removeSprite(sprite *s)
  {

	  spritesToRemove.push_back(s);
  }

  void world::updateSprites()
  {
	  if (spritesToAdd.size() != 0)
	  {
		  for (vector<sprite*>::iterator it = spritesToAdd.begin(); it != spritesToAdd.end(); ++it)
		  {
			  sprites.push_back(*it);
		  }

		  spritesToAdd.clear();
	  }

	  vector<sprite*> temp;

	  if (spritesToRemove.size() != 0)
	  {
		  for (vector<sprite*>::iterator it = spritesToRemove.begin(); it != spritesToRemove.end(); ++it)
		  {

			  for (vector<sprite*>::iterator it2 = sprites.begin(); it2 != sprites.end(); ++it2)
			  {
				  if (*it == *it2)
				  {
					  // do nothing
				  }
				  else
				  {
					  temp.push_back(*it2);
				  }
			  }
		  }
		  sprites = temp;
		  for (vector<sprite*>::iterator it = spritesToRemove.begin(); it != spritesToRemove.end(); ++it)
		  {
			  delete *it;
		  }
		  spritesToRemove.clear();
	  }
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
	  time += dt;
	  SpawnEnemies();
    for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
      (*it)->advance_by_time(dt);
    resolve_collisions();
	
	updateSprites();
  }

  void world::draw() 
  {
	  ALLEGRO_TRANSFORM t;
	  al_identity_transform(&t);
	  if (player != nullptr)
	  {
		  al_translate_transform(&t, -player->get_x() + 50, 0);
	  }

	  al_use_transform(&t);
	  al_clear_to_color(al_map_rgb(255,255,255));

	  int bgWidth = al_get_bitmap_width(background);

	  al_draw_bitmap(background, 0, 0, 0);
	  al_draw_bitmap(background, bgWidth, 0, 0);
	  al_draw_bitmap(background, bgWidth*2, 0, 0);

	  for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
		  (*it)->draw();


  }

  void world::SpawnEnemies()
  {
	  /*Spawn logic goes here, right now I just spawn a new enemy every 2 seconds*/
	  if ((time - lastSpawnTime) >= 2)
	  {
		  float x = player->get_x() + al_get_bitmap_width(background) + 20;
		  float y = player->get_y();
		  Enemy_Spawner* eSpawner = Enemy_Spawner::get();
		  sprite * s = eSpawner->SpawnEnemy(this, Enemy_Spawner::Tracker, x, y);
		  addSprite(s);
		  lastSpawnTime = time;
	  }
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
