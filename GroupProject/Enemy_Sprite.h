#ifndef __CDS_ENEMY_SPRITE_H
#define __CDS_ENEMY_SPRITE_H

#include "phys_sprite.h"
#include "world.h"
#include "image_sequence.h"
#include "player_missile.h"
#include "vec2d.h"

namespace csis3700 {

	class world;
	class phys_sprite;
	class player_missile;

	class Enemy_Sprite : public phys_sprite
	{
	public:
		
		~Enemy_Sprite();
		double GetPoints();
		Enemy_Sprite(world* w, float initX=0, float initialY=0);
		virtual void advance_by_time(double dt) = 0;
		virtual void die();
	protected:
		world * theWorld;
		double lifeSpan;
		double speedX;
		double speedY;
		double points;
		image_sequence* defaultSequence;
		void CheckBounds();
	};
}
#endif

