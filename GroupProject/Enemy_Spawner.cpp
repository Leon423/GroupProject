#include "stdafx.h"
#include "Enemy_Spawner.h"
#include <cassert>
#include "Enemy_Sprite.h"
#include "Enemy_Flyer.h"
#include "Enemy_Tracker.h"
#include "world.h"
namespace csis3700 {

	Enemy_Spawner *Enemy_Spawner::default_instance = NULL;

	Enemy_Spawner * Enemy_Spawner::get()
	{
		if (default_instance == NULL)
			default_instance = new Enemy_Spawner();
		return default_instance;
	}
	Enemy_Spawner::Enemy_Spawner()
	{
		
	}


	Enemy_Spawner::~Enemy_Spawner()
	{
	}
	Enemy_Sprite* Enemy_Spawner::SpawnEnemy(world* w, EnemyType e, float X, float Y)
	{
		if (e == Flyer)
		{
			return new Enemy_Flyer(w, X, Y);
		}
		else if (e == Tracker)
		{
			return new Enemy_Tracker(w, X, Y);
		}
		else if (e == TrackShoot)
		{

		}
		else if (e == FlyShoot)
		{

		}
		
		assert(false);
	}
}