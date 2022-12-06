/**
 * @file Laser.h
 * @brief
 *
 * @author
 * @bug
 */

#ifndef LASER_H
#define LASER_H

#include <allegro5/allegro.h>
#include <iostream>

#include "Point.h"
#include "Vector.h"
#include "Projectile.h"

class Laser : public Projectile {
  public:
    Laser (Point center, ALLEGRO_COLOR color, Vector movement, double angle);   
    ~Laser() {  };
    
    void hit();
    void draw();
    void loadAssets();

  protected:
  std::shared_ptr<Sprite> _sprite;
  int _angle;

};

#endif