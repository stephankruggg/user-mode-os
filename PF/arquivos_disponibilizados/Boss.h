
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
#include "traits.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

__BEGIN_API

class Boss : public Enemy {

  public:
    Boss (ALLEGRO_COLOR color, int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, double missileDelay, double laserDelay);
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

__END_API

#endif
