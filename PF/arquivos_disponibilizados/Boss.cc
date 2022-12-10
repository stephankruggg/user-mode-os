/**
 * @file Boss.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Boss.h"


__BEGIN_API

Boss::Boss(ALLEGRO_COLOR color, int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, double missileDelay, double laserDelay, Player * player) : Enemy(color, size, speed, maxLife, position, missileColor, laserColor, missileDelay, laserDelay) {
  _minXPosition = 700;
  _maxYPosition = 475;
  _minYPosition = 150;
  _player = player;
  loadSprites();
}

void Boss::draw() {
  chooseFrame();
  if (_life > 0) {
    _sprite->draw_boss(_spriteRow, _spriteCol, 200, 200, _center, 0);
  } else {
    drawDead();
  }
}

void Boss::move() {
  if (_center.x < _minXPosition) {
    if (_movement.x != 0) {
      reset_movement();
    }
  }
  else move_left();

  if (_center.y > _minYPosition && _movement.y <= 0) move_up();
  else if (_center.y < _maxYPosition && _movement.y >= 0) move_down();
  else reset_movement();
}

void Boss::shoot() {
  Point playerPosition = _player->getPosition();

  Vector firstMissileDirection(0, 0);
  firstMissileDirection.Angle(playerPosition, _center+Point(0, -7), 0.9);

  Vector secondMissileDirection(0, 0);
  secondMissileDirection.Angle(playerPosition, _center+Point(0, 7), 0.9);

  shootLasers({3, -3, 0}, {Vector(-500, 100), Vector(-500, -100), Vector(-500, 0)});
  shootMissiles({1, 1}, {firstMissileDirection, secondMissileDirection});
}

void Boss::chooseFrame() {
  if (_life == _maxLife) _spriteIndex = 0;

  if (_spriteIndex < 3) { 
    _size = 70;
    _spriteIndex++;
  }

  if (_life <= _maxLife / 2 && _spriteIndex < 8) {
    _size = 60;
    _spriteIndex++;
  }

  _spriteRow = _spriteIndex / 3;
  _spriteCol = _spriteIndex % 3;
}

void Boss::loadSprites() {
  _sprite = std::make_shared<Sprite>("bossv2.png");
}

__END_API