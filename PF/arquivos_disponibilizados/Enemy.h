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
#include "traits.h"

__BEGIN_API

class Enemy : public Spaceship {

  public:
    Enemy(ALLEGRO_COLOR color, int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, double missileDelay, double laserDelay, double hitDelay);
    ~Enemy() {  };

    virtual void draw() {  };
    virtual void loadSprites() {  };

    virtual void boundaryCollision(dir::direction direction) {  };
    
    virtual void move() {  };
    st::state run(double dt);

    virtual void shoot() {  };

  protected:
    ALLEGRO_COLOR _color;

    std::shared_ptr<Timer> _fireDelay;
    int _fireSpeed;

};

__END_API

#endif
