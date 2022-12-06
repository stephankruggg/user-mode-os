/**
 * @file Projectile.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Projectile.h"

Projectile::Projectile(Point center, ALLEGRO_COLOR color, Vector movement) {
  _center = center;
  _movement = movement;
  _color = color;
}

void Projectile::update(double dt) {
  _center = _center + _movement * dt;
}

Point Projectile::get_center() {
  return _center;
}

int Projectile::get_size() {
  return _size;
}
