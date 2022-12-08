/**
 * @file NormalEnemy.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "NormalEnemy.h"

__BEGIN_API

NormalEnemy::NormalEnemy(ALLEGRO_COLOR color, int size, int speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, int missileDelay, int laserDelay) : Enemy(color, size, speed, maxLife, position, missileColor, laserColor, missileDelay, laserDelay) {
  _deathAnimationFrame = 0;
  loadSprites();
  move();
}

void NormalEnemy::move() {
  move_left();
}

void NormalEnemy::shoot() {
  _missileMovement = Vector(-500, 0);
  _laserMovement = Vector(-300, 50);
  shootLasers({3, -3}, {Vector(-300, 50), Vector(-300, -50)});
}

void NormalEnemy::draw() {
  if (_life > 0) {
    _sprite->draw_tinted(_center, _color, 0);
  } else {
    drawDead();
  }      
}

void NormalEnemy::loadSprites() {
  _sprite = std::make_shared<Sprite>("EnemyBasic.png");
  _spriteDeath = std::make_shared<Sprite>("explode.png");
}

void NormalEnemy::boundaryCollision(dir::direction direction) {
  if (direction == dir::direction::LEFT) {
    _life = 0;
    reset_movement();
  }
}

__END_API
