/**
 * @file Enemy.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Enemy.h"

__BEGIN_API

Enemy::Enemy(ALLEGRO_COLOR color, int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, double missileDelay, double laserDelay) : Spaceship(size, speed, maxLife, position, missileColor, laserColor, missileDelay, laserDelay) {
  _color = color;
  _fireDelay = std::make_shared<Timer> (60);   
  _fireDelay->create();
  _fireDelay->startTimer();
  move();
}

st::state Enemy::run(double dt) {
  move();
  shoot();
  update(dt);
  return _currentState;
}

__END_API