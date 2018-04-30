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
#include "enemy_sprite.h"
#include <ctime>
#include <random>
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"

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
	  pickupSpawnAttempts = 0;
	  pickupSpawnFrequency = 3;

	  enemySpawnFrequency = 5;
	  currentLevel = 1;
	  LevelChangeScore = 1;

	  generator = minstd_rand(std::time(0));

	  font = al_load_font("Anonymous_Pro.ttf", 36, NULL);
	  backgroundMusic = al_load_sample("background.wav");

	  backgroundInstance = al_create_sample_instance(backgroundMusic);

	  al_set_sample_instance_playmode(backgroundInstance, ALLEGRO_PLAYMODE_LOOP);
	  al_attach_sample_instance_to_mixer(backgroundInstance, al_get_default_mixer());
	  al_set_sample_instance_gain(backgroundInstance, .2);

	  al_play_sample_instance(backgroundInstance);
	  

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
			  Enemy_Sprite* e = dynamic_cast<Enemy_Sprite*>(*it2);

			  if (e != NULL)
			  {
				  currentEnemyCount--;
			  }

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
	
	if (player->getScore() >= (LevelChangeScore*currentLevel))
	{
		UpdateLevel();
	}

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
	  // TODO: Update this to actually alternate the background. Probably gonna use sprites instead of just calling it here.
	  // ALSO NEED TO CHECK CURRENT LEVEL TO DRAW CORRECT BACKGROUND.

	 al_draw_bitmap(background, -bgWidth + bgWidth * backgroundPlayerIsIn, 0, 0);
	 al_draw_bitmap(background, 0 + bgWidth * backgroundPlayerIsIn, 0, 0);
	 al_draw_bitmap(background, bgWidth + bgWidth * backgroundPlayerIsIn, 0, 0);

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
	  
	  string str = std::to_string((int)player->getScore());

	  char * p = new char[str.length() + 1];
	  memcpy(p, str.c_str(), str.length() + 1);


	  al_draw_text(font, al_map_rgb(255, 255, 255), player->get_x() - 40, 0, ALLEGRO_ALIGN_LEFT, "SCORE:");
	  al_draw_textf(font, al_map_rgb(255, 255, 255), player->get_x() + 100, 0, ALLEGRO_ALIGN_LEFT, p);

  }

  void world::SpawnEnemies()
  {  
	  float spawnFreq = enemySpawnFrequency / currentLevel;
	  if (spawnFreq < 1)
		  spawnFreq = 1; // Dont want to spawn faster than 1 second.

	  
	  std::uniform_int_distribution<> dist(0, 3);
	  int nextRandomInt = dist(generator);
	  
	  if ((time - lastSpawnTime) >= spawnFreq && currentEnemyCount <= maxEnemyCount * currentLevel)
	  {
		  float x = player->get_x() + al_get_display_width(al_get_current_display()) + 20;
		  Enemy_Spawner* eSpawner = Enemy_Spawner::get();
		  sprite* s = NULL;
		  if (nextRandomInt == 0)
		  {
			  // spawn flyer
			  
			  float y = player->get_y();
			  s = eSpawner->SpawnEnemy(this, Enemy_Spawner::Flyer, x, y);
		  }
		  else if (nextRandomInt == 1)
		  {
			  // spawn tracker
			  // randomize the Y location
			  std::uniform_int_distribution<> dist(50, al_get_display_height(al_get_current_display()) - 50);
			  int randomY = dist(generator);
			  float y = player->get_y();
			  s = eSpawner->SpawnEnemy(this, Enemy_Spawner::Tracker, x, randomY);
		  }
		  else if (nextRandomInt == 2)
		  {
			  // spawn trackershoot
			  std::uniform_int_distribution<> dist(50, al_get_display_height(al_get_current_display()) - 50);
			  int randomY = dist(generator);
			  float y = player->get_y();
			  s = eSpawner->SpawnEnemy(this, Enemy_Spawner::TrackShoot, x, randomY);
		  }
		  else if (nextRandomInt == 3)
		  {
			  // spawn last enemy type
			  return;
		  }
		  if (s != NULL)
		  {
			  addSprite(s);
			  lastSpawnTime = time;
			  currentEnemyCount++;
		  }
	  }


	  /*
	  if ((time - lastSpawnTime) >= enemySpawnFrequency/currentLevel && currentEnemyCount <= maxEnemyCount*currentLevel)
	  {
		  float x = player->get_x() + al_get_bitmap_width(background) + 20;
		  float y = player->get_y();
		  Enemy_Spawner* eSpawner = Enemy_Spawner::get();
		  sprite * s = eSpawner->SpawnEnemy(this, Enemy_Spawner::TrackShoot, x, y);
		  addSprite(s);
		  lastSpawnTime = time;
		  currentEnemyCount++;
	  }
	  */
  }

  void world::UpdateLevel()
  {
	  if (currentLevel == 1)
	  {
		  image_library* lib = image_library::get();
		  background = lib->get("Galaxy.png");

		  al_stop_sample_instance(backgroundInstance);
		  al_destroy_sample(backgroundMusic);
		  al_destroy_sample_instance(backgroundInstance);
		  backgroundMusic = al_load_sample("background2.wav");
		  backgroundInstance = al_create_sample_instance(backgroundMusic);
		  al_set_sample_instance_playmode(backgroundInstance, ALLEGRO_PLAYMODE_LOOP);
		  al_attach_sample_instance_to_mixer(backgroundInstance, al_get_default_mixer());
		  al_set_sample_instance_gain(backgroundInstance, .2);

		  al_play_sample_instance(backgroundInstance);

		  
	  }
	  
	  currentLevel++;

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

  bool world::shouldSpawnPickup()
  {
	  pickupSpawnAttempts++;

	  if (pickupSpawnAttempts >= pickupSpawnFrequency)
	  {
		  pickupSpawnAttempts = 0;
		  return true;
	  }

	  return false;
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
