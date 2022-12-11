/**
 * @file Player.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Spaceship.h"
#include "Direction.h"
#include "traits.h"

__BEGIN_API

class Player : public Spaceship {

  public:
    Player(int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, double missileDelay, double laserDelay);
    ~Player() {  };

    void boundaryCollision(dir::direction direction);

    void shootL();
    void shootM();
    st::state run(double dt);

    void selectAnimation();
    void draw();
    void drawLife();
    void loadSprites();

};

__END_API

#endif
