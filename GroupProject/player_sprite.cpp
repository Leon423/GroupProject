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
using namespace std;

namespace csis3700 {

  player_sprite::player_sprite(world* w, float initial_x, float initial_y) : 
    phys_sprite(initial_x, initial_y) {

	  theWorld = w;
	  speedX = 200;
	  speedY = 100;
	  invincible = false;
	  timeOfBarrelRoll = 0;
	  barrelRollCooldown = 4.0;
	  barrelRollLength = 2.0;
	  set_position(vec2d(initial_x, initial_y));
	  maxMissiles = 3;
	  currentMissileCount = 0;
	  score = 0;
	  shotCooldown = 3.0;
	  lastShotTime = 0;
	  create_image_sequence();

  }

  void player_sprite::create_image_sequence()
  {
	  
	  /*TODO:	Add art to the Images folder and set this up for that artwork*/
	  defaultSequence = new image_sequence();
	  image_library *lib = image_library::get();
	  defaultSequence->add_image(lib->get("blah.jpg"), 0);
	  defaultSequence->add_image(lib->get("blah2.jpg"), 0.2);
	  defaultSequence->add_image(lib->get("blah.jpg"), 0.2);
	  set_image_sequence(defaultSequence);

	  // Add creation of barrell roll sequence here as well, right now I'm just gonna set it to the diagonal X and not animate it
	  barrelRollSequence = new image_sequence();
	  barrelRollSequence->add_image(lib->get("blah2.jpg"), 0);
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
	  // for now we just tell the world we died
	  theWorld->player_killed();
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
	  myShot = new player_missile(this, get_x() + 20, get_y());
	  currentMissileCount++;

	  theWorld->addSprite(myShot);
  }

  void player_sprite::RemoveMissile(player_missile * shot)
  {
	  score += shot->get_points();
	  currentMissileCount--;
	  theWorld->removeSprite(shot);
  }

}
