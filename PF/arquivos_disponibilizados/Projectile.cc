/**
 * @file Projectile.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Projectile.h"

__BEGIN_API

Projectile::Projectile(Point center, ALLEGRO_COLOR color, Vector movement) {
  _center = center;
  _movement = movement;
  _color = color;
}

void Projectile::update(double dt) {
  _center = _center + _movement * dt;
}

Point Projectile::getCenter() {
  return _center;
}

int Projectile::getSize() {
  return _size;
}

__END_API
