/**
 * @file Player.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Player.h"

__BEGIN_API

Player::Player(int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, int missileDelay, int laserDelay) : Spaceship(size, speed, maxLife, position, missileColor, laserColor, missileDelay, laserDelay) {
  _missileMovement = Vector(500, 0);
  _laserMovement = Vector(500, 0);
}

void Player::draw() {
  if (_life > 0) {
    _sprite->draw_region(_spriteRow, _spriteCol, 47.0, 40.0, _center, 0);
  } else {
    drawDead();
  } 
  drawLife();
}

void Player::selectAnimation() {
  if (_movement.y > 0) _spriteRow = 2;
  else if (_movement.y < 0) _spriteRow = 0;
  else _spriteRow = 1;

  if (_movement.x > 0) _spriteCol = 1;
  else _spriteCol = 0;
}

void Player::drawLife() {
  al_draw_line(_center.x - _size*2, _center.y + _size*2, (_center.x - _size*2) + (_life / _maxLife) * (_size*4), _center.y + _size*2,
		al_map_rgb(255 * (1.0 - _life / _maxLife), 200 * (_life / _maxLife), 0), 5);
}

void Player::update(double dt) {
  _center = _center + _movement * dt;
  updateLasers(dt);
  updateMissiles(dt);
  resetTimers();
  selectAnimation();
  reset_movement();
}

void Player::loadSprites() {
  _sprite = std::make_shared<Sprite>("Player.png");
}

void Player::boundaryCollision(dir::direction direction) {
  reset_movement();
  switch (direction) {
    case dir::UP:
      _center.y = 0 + _size - 20;
      break;
    case dir::DOWN:
      _center.y = 600 - _size + 20;
      break;
    case dir::LEFT:
      _center.x = _size - 20;
      break;
    case dir::RIGHT:
      _center.x = 800 - _size + 20;
      break;
  }
}

void Player::shootM() {
  shootMissiles({-1}, {_missileMovement});
}

void Player::shootL() {
  shootLasers({0}, {_laserMovement});
}

__END_API
