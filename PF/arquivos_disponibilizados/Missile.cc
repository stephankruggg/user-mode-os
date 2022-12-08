/**
 * @file Missile.cc
 * @briefbgMid
 *
 * @author
 * @bug
 */

#include "Missile.h"
#include <cmath>
#include "Sprite.h"

__BEGIN_API

Missile::Missile(Point p, ALLEGRO_COLOR c, Vector s, double angle) : Projectile(p, c, s)
{
  _angle = atan(_movement.y / _movement.x) + angle * 4.71;
  _center = _center + _movement * 0.1;
  _sprite_number = 0;
  _size = 10;

  _sprite_names = {"m1.png", "m2.png", "m3.png", "m4.png", "m5.png", "m6.png", "m7.png", "m8.png"};
  loadAssets();
}

void Missile::loadAssets() {
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));  
  
  for (auto &s : _sprite_names) {
    _sprite_list.push_back(std::make_shared<Sprite> (s));
  }

  al_destroy_path(path);
}

void Missile::hit() {  }

void Missile::draw() {
  _sprite_list[_sprite_number]->draw_rotated(_center, _angle, 0);
  _sprite_number++;

  if (_sprite_number == _sprite_list.size()) _sprite_number = 0;
}

__END_API
