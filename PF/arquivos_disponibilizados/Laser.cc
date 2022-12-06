/**
 * @file Laser.cc
 * @brief
 *
 * @author
 */
#include "Laser.h"

#include <allegro5/allegro_primitives.h>

Laser::Laser(Point center, ALLEGRO_COLOR color, Vector movement, double angle) : Projectile(center, color, movement)
{
  _size = -0.05;
  _center = _center + _movement * 0.1;
  _angle = angle;
  loadAssets();
}

void Laser::draw() {
  _sprite->draw_rotated(_center, _angle, 2);
}

void Laser::loadAssets() {
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));  
  
  _sprite = std::make_shared<Sprite>("Laser.png");

  al_destroy_path(path);
}

void Laser::hit() {
}
