#include "stdafx.h"

#include "player_sprite.h"
#include "image_library.h"
#include "image_sequence.h"
#include "vec2d.h"
#include "collision.h"
#include <cmath>
#include "world.h"
#include "keyboard_manager.h"
#include "obstruction_sprite.h"
#include "enemy_missile.h"
#include "pickup.h"
#include "allegro5\allegro_audio.h"
#include "allegro5\allegro_acodec.h"

using namespace std;

namespace csis3700 {

  player_sprite::player_sprite(world* w, float initial_x, float initial_y) : 
    phys_sprite(initial_x, initial_y) {

	  theWorld = w;
	  speedX = 200;
	  speedY = 200;
	  invincible = false;
	  timeOfBarrelRoll = 0;
	  barrelRollCooldown = 4.0;
	  barrelRollLength = 2.0;
	  set_position(vec2d(initial_x, initial_y));
	  maxMissiles = 3;
	  currentMissileCount = 0;
	  score = 0;
	  shotCooldown = 1.5;
	  minimumFireRate = .5;
	  lastShotTime = 0;
	  collisionChan = Player;
	  dieSound = al_load_sample("explosion.wav");
	  fireSound = al_load_sample("fire.wav");
	  create_image_sequence();

  }

  void player_sprite::create_image_sequence()
  {
	  
	  /*TODO:	Add art to the Images folder and set this up for that artwork*/
	  defaultSequence = new image_sequence();
	  image_library *lib = image_library::get();
	  defaultSequence->add_image(lib->get("hero2.png"), 0);
	  defaultSequence->add_image(lib->get("hero3.png"), 0.2);
	  defaultSequence->add_image(lib->get("hero4.png"), 0.2);
	  //defaultSequence->add_image(lib->get("hero5.png"), 0.2);
	  //defaultSequence->add_image(lib->get("hero4.png"), 0.2);
	  defaultSequence->add_image(lib->get("hero3.png"), 0.2);
	  defaultSequence->add_image(lib->get("hero2.png"), 0.2);
	  set_image_sequence(defaultSequence);

	  // Add creation of barrell roll sequence here as well, right now I'm just gonna set it to the diagonal X and not animate it
	  barrelRollSequence = new image_sequence();
	  barrelRollSequence->add_image(lib->get("hero1.png"), 0);
	  barrelRollSequence->add_image(lib->get("hero2.png"), 0.1);
	  barrelRollSequence->add_image(lib->get("hero1_flip.png"), 0.2);
	  barrelRollSequence->add_image(lib->get("hero1.png"), 0.1);
  }

  void player_sprite::advance_by_time(double dt) {

	  if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_UP) && keyboard_manager::get()->is_key_down(ALLEGRO_KEY_DOWN))
		  set_velocity(vec2d(speedX, 0));
	  else if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_UP))
		  set_velocity(vec2d(speedX, -speedY));
	  else if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_DOWN))
		  set_velocity(vec2d(speedX, speedY));
	  else
		  set_velocity(vec2d(speedX, 0));

	  if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_Q) && canBarrelRoll())
	  {
		  DoABarrelRoll(dt);
	  }

	  if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_SPACE) && canFire())
	  {
		  Fire();
	  }

	  if (invincible)
	  {
		  // currently barrel rolling, check the reset on it
		  if ((time - timeOfBarrelRoll) >= barrelRollLength)
		  {
			  invincible = false;
			  set_image_sequence(defaultSequence);
		  }
	  }

	  phys_sprite::advance_by_time(dt);
  }

  void player_sprite::resolve(const collision& collision, sprite* other)
  {
	  if (other->GetCollisionChannel() == PlayerMissile)
		  return;

	  if (other->GetCollisionChannel() == Enemy && !invincible)
	  {
		  // we hit an enemy or a missile, so we died!

		  enemy_missile *s = dynamic_cast<enemy_missile*>(other);

		  if (s != NULL)
		  {
			  s->collidedWithPlayer();
		  }

		  al_play_sample(dieSound, 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

		  theWorld->player_killed();
		  return;
	  }

	  if (other->GetCollisionChannel() == Collectible)
	  {
		  // do powerup, coins, whatever thing
		  pickup* p = dynamic_cast<pickup*>(other);

		  if (p != NULL)
		  {
			  p->OnPickup(this);
		  }
	  }
  }

  void player_sprite::DoABarrelRoll(double dt)
  {
	  timeOfBarrelRoll = time;
	  invincible = true;
	  set_image_sequence(barrelRollSequence);
  }

  bool player_sprite::canBarrelRoll()
  {
	  if ((time - timeOfBarrelRoll) >= barrelRollCooldown)
	  {
		  return true;
	  }

	  return false;
  }

  bool player_sprite::canFire()
  {
	  if (currentMissileCount < maxMissiles && (time - lastShotTime) >= shotCooldown)
	  {
		  lastShotTime = time;
		  return true;
	  }

	  return false;
  }

  void player_sprite::Fire()
  {
	  float spawnX = get_x() + get_width();
	  float spawnY = get_y() + get_height() / 2;

	  spawnY -= 10;

	  al_play_sample(fireSound, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

	  player_missile *myShot = new player_missile(this, spawnX, spawnY);
	  currentMissileCount++;

	  theWorld->addSprite(myShot);
  }

  void player_sprite::RemoveMissile(player_missile * shot)
  {
	  score += shot->get_points();
	  currentMissileCount--;
	  //theWorld->removeSprite(shot);
  }

  double player_sprite::getScore()
  {
	  return score;
  }
  void player_sprite::IncreaseFireRate(double increase)
  {
	  shotCooldown -= increase;

	  if (shotCooldown <= minimumFireRate)
	  {
		  shotCooldown = minimumFireRate;
	  }
  }
}
