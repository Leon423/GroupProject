#ifndef __CDS_PLAYER_SPRITE_H
#define __CDS_PLAYER_SPRITE_H
#include "phys_sprite.h"
#include "world.h"
#include "image_sequence.h"
#include "player_missile.h"
#include "allegro5\allegro_audio.h"
#include "allegro5\allegro_acodec.h"

namespace csis3700 {

	class world;
	class image_sequence;
	class player_missile;

  class player_sprite : public phys_sprite {
  public:
    player_sprite(world* w, float initial_x=0, float initial_y=0);
    virtual void advance_by_time(double dt);

	virtual bool is_player()
	{
		return true;
	}

	virtual void resolve(const collision& collision, sprite* other);

	bool is_invincible()
	{
		return invincible;
	}

	void DoABarrelRoll(double dt);

	bool canBarrelRoll();

	bool canFire();

	void Fire();

	void RemoveMissile(player_missile *shot);

	double getScore();

	void IncreaseFireRate(double increase);

  private:
	  // pointer to the world
	  world *theWorld;
	  void create_image_sequence();
	  // the default animation that plays
	  image_sequence *defaultSequence;
	  // animation for the barrel roll
	  image_sequence *barrelRollSequence;
	  // barrel roll makes you invincible
	  bool invincible;
	  //Stores the time that the last barrel roll was activated
	  double timeOfBarrelRoll;
	  // The total time between starting a barrel roll and being able to do another one
	  double barrelRollCooldown;
	  // The length of time that you are invincible from a barrel roll.
	  double barrelRollLength;
	  // max number of missiles allowed on screen at once
	  int maxMissiles;
	  int currentMissileCount;
	  // time between missile fires
	  double shotCooldown;
	  //fastest firerate
	  double minimumFireRate;
	  // time of last shot
	  double lastShotTime;
	  // Score
	  double score;

	  double speedX;
	  double speedY;
	  ALLEGRO_SAMPLE* fireSound;
	  ALLEGRO_SAMPLE* dieSound;

  };
}


#endif /* PLAYER_SPRITE_H */
