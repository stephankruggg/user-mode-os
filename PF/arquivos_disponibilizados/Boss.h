
/**
 * @file Boss.h
 * @brief
 *
 * @author
 * @bugs lots
 *
 **/

#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

class Boss : public Enemy {

  public:
    Boss (ALLEGRO_COLOR color, int size, int speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, int missileDelay, int laserDelay);
    ~Boss() {  };
    
    void move();
    void shoot();

    void chooseFrame();
    void draw();

    void loadSprites();

  protected:
    int _maxYPosition;
    int _minYPosition;
    int _minXPosition;

    int _spriteIndex;

};
#endif