#include "stdafx.h"
#include "Enemy_Sprite.h"
#include "player_missile.h"
#include "vec2d.h"

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
	}
	void Enemy_Sprite::die()
	{
		isDead = true;
		theWorld->removeEnemy(this);
	}

	void Enemy_Sprite::CheckBounds()
	{
		float playerX = theWorld->get_player()->get_x();

		if ((playerX - 10) >= get_x())
		{
			theWorld->removeEnemy(this);
			isDead = true;
		}
	}
}