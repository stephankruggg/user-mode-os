/**
 * @file Player.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Player.h"

__BEGIN_API

Player::Player(int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, double missileDelay, double laserDelay, double hitDelay) : Spaceship(size, speed, maxLife, position, missileColor, laserColor, missileDelay, laserDelay, hitDelay) {
  _missileMovement = Vector(500, 0);
  _laserMovement = Vector(500, 0);
  _deathAnimationFrame = 0;
}

void Player::draw() {
  if (_life > 0) {
    _sprite->draw_region(_spriteRow, _spriteCol, 47.0, 40.0, _center, 0);
  } else {
    drawDead();
  }
}

void Player::selectAnimation() {
  if (_movement.y > 0) _spriteRow = 2;
  else if (_movement.y < 0) _spriteRow = 0;
  else _spriteRow = 1;

  if (_movement.x > 0) _spriteCol = 1;
  else _spriteCol = 0;
}

void Player::drawLife() {
  int xPosition = 750;
  int yPosition = 20;
  int xOffset = 20;
  int yOffset = 20;

  for (int i = 0; i < _life; ++i) {
    al_draw_rectangle(xPosition, yPosition, xPosition + xOffset, yPosition + yOffset, al_map_rgb(0, 255, 0), 1);
    xPosition -= 30;
  }
}

st::state Player::run(double dt) {
  _center = _center + _movement * dt;
  updateLasers(dt);
  updateMissiles(dt);
  resetTimers();
  selectAnimation();
  resetMovement();
  return _currentState;
}

void Player::loadSprites() {
  _sprite = std::make_shared<Sprite>("Player.png");
  _spriteDeath = std::make_shared<Sprite>("explode.png");
}

void Player::boundaryCollision(dir::direction direction) {
  resetMovement();
  switch (direction) {
    case dir::UP:
      _center.y = _size / 2 + 1;
      break;
    case dir::DOWN:
      _center.y = 600 - _size / 2 - 1;
      break;
    case dir::LEFT:
      _center.x = _size / 2 + 1;
      break;
    case dir::RIGHT:
      _center.x = 800 - _size / 2 - 1;
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
