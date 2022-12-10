/**
 * @file Enemy.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Enemy.h"

__BEGIN_API

Enemy::Enemy(ALLEGRO_COLOR color, int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, int missileDelay, int laserDelay) : Spaceship(size, speed, maxLife, position, missileColor, laserColor, missileDelay, laserDelay) {
  _color = color;
  _fireDelay = std::make_shared<Timer> (60);   
  _fireDelay->create();
  _fireDelay->startTimer();
  move();
}

void Enemy::run(double dt) {
  move();
  shoot();
  update(dt);
}

__END_API