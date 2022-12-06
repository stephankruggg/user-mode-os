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

class Player : public Spaceship {

  public:
    Player(int size, int speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, int missileDelay, int laserDelay);
    ~Player();

    void boundaryCollision(dir::direction direction);

    void shootL();
    void shootM();
    void update(double dt);

    void selectAnimation();
    void draw();
    void drawLife();
    void loadSprites();

};

#endif
