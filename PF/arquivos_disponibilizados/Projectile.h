/**
 * @file Projectile.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <memory>
#include <iostream>
#include "Sprite.h"
#include "Point.h"
#include "Vector.h"
#include "traits.h"

__BEGIN_API

class Projectile {

  public:
    Projectile(Point center, ALLEGRO_COLOR color, Vector movement);
    ~Projectile() {  };

    void update(double dt);

    virtual void hit() {  };

    virtual void draw() {  };

    Point get_center();
    int get_size();

  protected:
    int _size;

    ALLEGRO_COLOR _color;

    Point _center;
    Vector _movement;

};

__END_API

#endif
