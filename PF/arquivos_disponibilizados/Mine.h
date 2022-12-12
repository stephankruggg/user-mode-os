/**
 * @file Mine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef MINE_H
#define MINE_H

#include "Enemy.h"
#include "traits.h"

__BEGIN_API

class Mine : public Enemy {

  public:
    Mine(ALLEGRO_COLOR _color, int size, int speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, double missileDelay, double laserDelay, double hitDelay);
    ~Mine() {  };

    void boundaryCollision(dir::direction direction) {  };
    void move();
    void shoot();
    void drawDead();
    void die();

    void draw();
    void loadSprites();
    void chooseFrame();

  protected:
    std::shared_ptr<Timer> _timer;
};

__END_API

#endif