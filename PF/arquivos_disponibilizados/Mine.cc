/**
 * @file Mine.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Mine.h"

__BEGIN_API

Mine::Mine(ALLEGRO_COLOR color, int size, int speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, double missileDelay, double laserDelay, double hitDelay) : Enemy(color, size, speed, maxLife, position, missileColor, laserColor, missileDelay, laserDelay, hitDelay) {
  _deathAnimationFrame = 0;
  loadSprites();
  move();
  
  _timer = std::make_shared<Timer> (1);
  _timer->create();
  _timer->startTimer();

  _spriteCol = 0;
  _spriteRow = rand() % 3; 
}

void Mine::move() {
  if (_center.x >= 400) move_left();
  else reset_movement();
}

void Mine::shoot() {
  if (_timer->getCount() >= 5 && _life > 0) {
    _life = 0;
    _size = 0;
    shootLasers({2, -2, 2, -2, -3, 3, -3, 3, 0, 0}, {Vector(-250, 250), Vector(250, 250), Vector(250, -250), Vector(-250, -250), Vector(-400, -100), Vector(-400, 100), Vector(400, 100), Vector(400, -100), Vector(-500, 0), Vector(500, 0)});
  }
}

void Mine::draw() {
  if (_life > 0) {
    chooseFrame();
    _sprite->draw_region(_spriteRow, _spriteCol, 40.0, 40.0, _center, 0);
  } else {
    drawDead();
  }
}

void Mine::chooseFrame() {
  if (_life < _maxLife * 2 / 3 && _life > _maxLife / 3) _spriteCol = 1;
  if (_life < _maxLife / 3) _spriteCol = 2;
}

void Mine::loadSprites() {
  _sprite = std::make_shared<Sprite>("spikebomb.png");
  _spriteDeath = std::make_shared<Sprite>("explode.png");
}

void Mine::drawDead() {
  if (_deathAnimationFrame < 5) deathAnimation();
  else die();
}

void Mine::die() {
  if (_timer->getCount() > 10) _currentState = st::DEAD;
}

__END_API
