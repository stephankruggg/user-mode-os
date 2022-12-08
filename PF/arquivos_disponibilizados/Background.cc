/**
 * @file Background.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Background.h"

__BEGIN_API

Background::Background() {
  _bgPoint = Point(0, 0);
  _bgMovement = Vector(50, 0);
  _bgMaxXPosition = 800;
}

void Background::draw() {
  _bg->draw_parallax_background(_bgPoint.x, 0);
}

void Background::loadSprites() {
  _bg = std::make_shared<Sprite>("BGstars.png");
}

void Background::update(double dt) {
  _bgPoint = _bgPoint + _bgMovement * dt;

  if (_bgPoint.x >= _bgMaxXPosition) {
    _bgPoint.x = 0;
  }
}

__END_API