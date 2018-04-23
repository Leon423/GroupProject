#ifndef __CDS_ENEMY_SPAWNER_H
#define __CDS_ENEMY_SPAWNER_H

#include "Enemy_Sprite.h"

/*Singleton class used to spawn enemies. This is primarily used by The World, but I might want to be able
to have a badguy that can spawn enemies, so it is now a Singleton*/

namespace csis3700 {

	class Enemy_Sprite;

	class Enemy_Spawner
	{
	public:
		/*Fetches the enemy spawner instance, there is only one.
		Call with Enemy_Spawner::get()*/
		static Enemy_Spawner *get();
		enum EnemyType
		{
			Flyer, Tracker, FlyShoot, TrackShoot, Boss1, Boss2
		};

		Enemy_Spawner();
		~Enemy_Spawner();

		Enemy_Sprite* SpawnEnemy(world * w, EnemyType e, float X, float Y);

	private:
		static Enemy_Spawner *default_instance;
	};
}

#endif
