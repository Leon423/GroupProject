#include "stdafx.h"

#include "sprite.h"
#include "phys_sprite.h"
#include <vector>
using namespace std;

namespace csis3700 {
  
  phys_sprite::phys_sprite(float initial_x, float initial_y, float initial_vx, float initial_vy) : sprite(initial_x, initial_y) {
    velocity = vec2d(initial_vx, initial_vy);
  }

  void phys_sprite::advance_by_time(double dt) {
    sprite::advance_by_time(dt);
    position = position + dt * velocity;
    velocity = velocity + dt * get_acceleration();
  }

  void phys_sprite::set_velocity(const vec2d& v) {
    velocity = v;
  }

  vec2d phys_sprite::get_acceleration() const {
    return acceleration;
  }

  void phys_sprite::set_acceleration(const vec2d& v) {
    acceleration = v;
  }

  vec2d phys_sprite::get_velocity() const {
    return velocity;
  }

}

