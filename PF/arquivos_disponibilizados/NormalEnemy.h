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

class NormalEnemy : public Enemy {

  public:
    NormalEnemy(ALLEGRO_COLOR _color, int size, int speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, int missileDelay, int laserDelay);
    ~NormalEnemy() {  };

    void boundaryCollision(dir::direction direction);
    void move();
    void shoot();

    void draw();
    void loadSprites();

};

#endif
