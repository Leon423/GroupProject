#ifndef __CDS_WORLD_H
#define __CDS_WORLD_H

#include "allegro5/allegro.h"
#include "sprite.h"
#include "player_sprite.h"
#include <vector>
#include "Enemy_Spawner.h"
#include "enemy_missile.h"

namespace csis3700 {

	class player_sprite;
	class Enemy_Spawner;
	class enemy_missile;

  class world {
  public:
    /**
     * Construct the world. The display is passed in simply to make it
     * possible to modify options or access the backbuffer. DO NOT
     * store the display in an instance variable. DO NOT start drawing
     * on the screen. Just load bitmaps etc.
     */
    world();

    /**
     * Free any resources being used by the world.
     */
    ~world();

    /**
     * Block the copy constructor.  Worlds should not be copied to
     * just assert(false)
     */
    world(const world& other);

    /**
     * Block operator =.  Worlds should not be assigned.
     */
    world& operator =(const world& other);
 
    /**
     * Update the state of the world based on the event ev.
     */
    void handle_event(ALLEGRO_EVENT ev);

    /**
     * Advance the state of the world forward by the specified time.
     */
    void advance_by_time(double dt);

    /**
     * Draw the world. Note that the display variable is passed only
     * because it might be needed to switch the target bitmap back to
     * the backbuffer.
     */
    void draw();

    /**
     * Return true iff game is over and window should close
     */
    bool should_exit();

	void player_killed();

	void addSprite(sprite *s);

	void removeSprite(sprite *s);

	const player_sprite * get_player()
	{
		return player;
	}

	void removeEnemy(sprite * s);

	void addMissile(enemy_missile* missile);

  private:
    void resolve_collisions();
    player_sprite *player;
    std::vector<sprite*> sprites;
	ALLEGRO_BITMAP *background;

	/**
	Create Sprites necessary for the start of the level. Usually the player!
	*/
	void create_sprites();

	void handle_collisions(std::vector<collision>&);

	void updateSprites();

	void SpawnEnemies();

	double lastSpawnTime;
	/*Time since creation*/
	double time;

	/*Keep track of sprites to add and to remove until after collisions are resolved or time is advanced*/
	std::vector<sprite*> spritesToAdd;
	std::vector<sprite*> spritesToRemove;
	std::vector<enemy_missile*> missileSprites;
	std::vector<enemy_missile*> missilesToAdd;
	bool playerKilled;

	int currentEnemyCount;
	int maxEnemyCount;

	
  };
}

#endif /* WORLD_H */
