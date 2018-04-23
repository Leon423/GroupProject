#include "stdafx.h"
#include "Enemy_Sprite.h"
#include "player_missile.h"
#include "vec2d.h"

namespace csis3700 {
	Enemy_Sprite::Enemy_Sprite()
	{
		collisionChan = Enemy;
	}
	double Enemy_Sprite::GetPoints()
	{
		return points;
	}
	Enemy_Sprite::Enemy_Sprite(world * w, float initX, float initialY)
	{
		theWorld = w;
		set_position(vec2d(initX, initialY));
	}
	void Enemy_Sprite::die()
	{
		theWorld->removeSprite(this);
	}
}