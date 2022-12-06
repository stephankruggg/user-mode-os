/**
 * @file Missile.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef MISSILE_H
#define MISSILE_H

#include <allegro5/allegro.h>

#include <memory>
#include <vector>
#include <iostream>

#include "Point.h"
#include "Vector.h"
#include "Projectile.h"
#include "Sprite.h"

class Missile : public Projectile {   
  public:
    Missile(Point center, ALLEGRO_COLOR color, Vector movement, double angle);
    ~Missile() {  };

    void draw();
    void hit();

    void loadAssets();
    
  private:
    std::vector<std::shared_ptr<Sprite>> _sprite_list;
    long unsigned int _sprite_number;

    double _angle;

    std::vector<char *> _sprite_names;
   
};

#endif
