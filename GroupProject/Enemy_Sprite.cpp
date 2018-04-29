#include "stdafx.h"
#include "Enemy_Sprite.h"
#include "player_missile.h"
#include "vec2d.h"
#include "pickup.h"
#include "pickup_firerate.h"
#include "allegro5\allegro_audio.h"
#include "allegro5\allegro_acodec.h"


namespace csis3700 {
	Enemy_Sprite::~Enemy_Sprite()
	{
		theWorld = nullptr;
		delete defaultSequence;
		defaultSequence = nullptr;
		
	}
	double Enemy_Sprite::GetPoints()
	{
		return points;
	}
	Enemy_Sprite::Enemy_Sprite(world * w, float initX, float initialY) : phys_sprite(initX, initialY)
	{
		theWorld = w;
		collisionChan = Enemy;
		points = 1;
		dieSound = al_load_sample("explosion.wav");
	}
	void Enemy_Sprite::die()
	{
		SpawnPickup();

		al_play_sample(dieSound, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

		isDead = true;
		//theWorld->removeEnemy(this);
	}

	void Enemy_Sprite::CheckBounds()
	{
		float playerX = theWorld->get_player()->get_x();

		if ((playerX - 100) >= get_x())
		{
			theWorld->removeEnemy(this);
			isDead = true;
		}
	}
	void Enemy_Sprite::SpawnPickup()
	{
		// do nothing if we have no pickup to spawn.
	}
}