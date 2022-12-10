/**
 * @file NormalEnemy.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef NormalEnemy_H
#define NORMALENEMY_H

#include "Enemy.h"
#include "Direction.h"
#include "traits.h"

__BEGIN_API

class NormalEnemy : public Enemy {

  public:
    NormalEnemy(ALLEGRO_COLOR _color, int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, double missileDelay, double laserDelay);
    ~NormalEnemy() {  };

    void boundaryCollision(dir::direction direction);
    void move();
    void shoot();

    void draw();
    void loadSprites();

};

__END_API

#endif
