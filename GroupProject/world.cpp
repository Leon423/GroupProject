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
#include <vector>
#include "enemy_missile.h"

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
	  currentEnemyCount = 0;
	  maxEnemyCount = 5;
	  playerKilled = false;
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
	  vector<int> indexRemoved;
	  int currentIndex = 0;
	  for (vector<sprite*>::iterator it2 = sprites.begin(); it2 != sprites.end(); it2++)
	  {
		  if ((*it2)->is_dead())
		  {
			  indexRemoved.push_back(currentIndex);
		  }
		  currentIndex++;
	  }

	  for (int i = indexRemoved.size(); i > 0; i--)
	  {
		  sprites.erase(sprites.begin() + indexRemoved.at(i-1));
	  }

	  //sprites.shrink_to_fit();

	  indexRemoved = vector<int>();

	  currentIndex = 0;
	  for (vector<enemy_missile*>::iterator it = missileSprites.begin(); it != missileSprites.end(); ++it)
	  {
		  if ((*it)->is_dead())
		  {
			  indexRemoved.push_back(currentIndex);
		  }

		  currentIndex++;
	  }

	  for (int i = indexRemoved.size(); i > 0; i--)
	  {
		  missileSprites.erase(missileSprites.begin() + indexRemoved.at(i-1));
	  }

	  if (playerKilled)
	  {
		  spritesToAdd.erase(spritesToAdd.begin(), spritesToAdd.end());
		  missilesToAdd.erase(missilesToAdd.begin(), missilesToAdd.end());
		  return;
	  }
		  

	  if (spritesToAdd.size() != 0)
	  {
		  for (vector<sprite*>::iterator it = spritesToAdd.begin(); it != spritesToAdd.end(); ++it)
		  {
			  sprites.push_back(*it);
		  }

		  spritesToAdd.clear();
	  }

	  if (missilesToAdd.size() != 0)
	  {
		  for (vector<enemy_missile*>::iterator it = missilesToAdd.begin(); it != missilesToAdd.end(); ++it)
		  {
			  missileSprites.push_back(*it);
		  }

		  missilesToAdd.clear();
	  }


	  

	  /*
	  vector<int> indexRemoved;
	  
	  if (spritesToRemove.size() != 0)
	  {
		  for (vector<sprite*>::iterator it = spritesToRemove.begin(); it != spritesToRemove.end(); ++it)
		  {
			  int currentindex = 0;
			  for (vector<sprite*>::iterator it2 = sprites.begin(); it2 != sprites.end(); it2++)
			  {
				  if (*it == *it2)
				  {
					  // remove
					  indexRemoved.push_back(currentindex);
				  }

				  currentindex++;
			  }
		  }

		  for (int i = 0; i < indexRemoved.size(); i++)
		  {
			  sprites.erase(sprites.begin() + indexRemoved.at(i));
		  }

		  //spritesToRemove.clear();
	  }
	  */

	  /*

	  FIRST VERSION: CAUSES A MEMORY ACCESS VIOLATION

	  vector<sprite*> temp;
	  
	  if (spritesToRemove.size() != 0)
	  {
		  for (vector<sprite*>::iterator it = spritesToRemove.begin(); it != spritesToRemove.end(); ++it)
		  {

			  for (vector<sprite*>::iterator it2 = sprites.begin(); it2 != sprites.end(); ++it2)
			  {
				  if (*it == *it2)
				  {
					  //printf("I'm happening\n");
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
	  */
	  
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

	  for (auto i = missileSprites.begin(); i != missileSprites.end(); ++i)
	  {
		  if ((*i)->collides_with(*player))
		  {
			  collisions.push_back(collision(*i, player));
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
	for (vector<enemy_missile*>::iterator it = missileSprites.begin(); it != missileSprites.end(); ++it)
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
	  float x = player->get_x();
	  int backgroundPlayerIsIn = x / bgWidth;

	  al_draw_bitmap(background, -bgWidth + bgWidth*backgroundPlayerIsIn, 0, 0);
	  al_draw_bitmap(background, 0 + bgWidth*backgroundPlayerIsIn, 0, 0);
	  al_draw_bitmap(background, bgWidth + bgWidth*backgroundPlayerIsIn, 0, 0);

	  for (vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	  {
		 if(*it != NULL)
			(*it)->draw();
		  
	  }

	  for (vector<enemy_missile*>::iterator it = missileSprites.begin(); it != missileSprites.end(); ++it)
	  {
		  if (*it != NULL)
			  (*it)->draw();

	  }

  }

  void world::SpawnEnemies()
  {
	  /*Spawn logic goes here, right now I just spawn a new enemy every 2 seconds*/
	  if ((time - lastSpawnTime) >= 1 && currentEnemyCount <= maxEnemyCount)
	  {
		  float x = player->get_x() + al_get_bitmap_width(background) + 20;
		  float y = player->get_y();
		  Enemy_Spawner* eSpawner = Enemy_Spawner::get();
		  sprite * s = eSpawner->SpawnEnemy(this, Enemy_Spawner::TrackShoot, x, y);
		  addSprite(s);
		  lastSpawnTime = time;
		  currentEnemyCount++;
	  }
  }

  void world::removeEnemy(sprite * s)
  {
	  currentEnemyCount--;
	  //removeSprite(s);
  }

  void world::addMissile(enemy_missile * missile)
  {
	  missilesToAdd.push_back(missile);
  }

  bool world::should_exit() {
    return false;
  }

  void world::player_killed()
  {
	  if (sprites.front()->is_player())
		  sprites.erase(sprites.begin());
	  playerKilled = true;
  }

}
