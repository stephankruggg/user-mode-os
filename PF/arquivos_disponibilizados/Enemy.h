/**
 * @file Enemy.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef Enemy_H
#define Enemy_H

#include "Spaceship.h"
#include "Timer.h"
#include "Direction.h"

class Enemy : public Spaceship {

  public:
    Enemy(ALLEGRO_COLOR color, int size, int speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, int missileDelay, int laserDelay);
    ~Enemy() {  };

    virtual void draw() {  };
    virtual void loadSprites() {  };

    virtual void boundaryCollision(dir::direction direction) {  };
    
    virtual void move() {  };
    void run(double dt);

    virtual void shoot() {  };

  protected:
    ALLEGRO_COLOR _color;

    std::shared_ptr<Timer> _fireDelay;
    int _fireSpeed;

};

#endif
