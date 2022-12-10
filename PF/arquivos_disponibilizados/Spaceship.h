/**
 * @file Spaceship.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Vector.h"
#include "Point.h"
#include "Sprite.h"
#include "Missile.h"
#include "Laser.h"
#include "Timer.h"
#include <iostream>
#include <memory>
#include "traits.h"

__BEGIN_API

class Spaceship {

  public:
    Spaceship(int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, int missileDelay, int laserDelay);
    ~Spaceship() {  };

    void update(double dt);

    virtual void draw() {  };
    virtual void loadSprites() {  };
    void drawDead();

    void reset_movement();
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    virtual void boundaryCollision() {  };
    void laserCollision(Laser * laser);
    void missileCollision(Missile * missile);

    void shootLasers(std::vector<double> angles, std::vector<Vector> movements);
    void shootMissiles(std::vector<double> angles, std::vector<Vector> movements);

    void take_hit();

    Point get_center();
    int get_size();

    void deathAnimation();
    void die();

    std::vector<Laser*> getCurrentLasers();
    std::vector<Missile*> getCurrentMissiles();

    void updateLasers(double dt);
    void updateMissiles(double dt);
    void resetTimers();

  protected:
    int _maxLife;
    int _life;
    int _size;

    double _speed;
    Vector _movement;
    Point _center;

    std::shared_ptr<Sprite> _sprite;
    int _spriteRow;
    int _spriteCol;

    int _deathAnimationFrame;
    std::shared_ptr<Sprite> _spriteDeath;

    ALLEGRO_COLOR _missileColor;
    ALLEGRO_COLOR _laserColor;

    std::vector<Laser *> _currentLasers;
    std::vector<Missile *> _currentMissiles;

    std::shared_ptr<Timer> _laserTimer;
    std::shared_ptr<Timer> _missileTimer;
    int _laserDelay;
    int _missileDelay;
    Vector _missileMovement;
    Vector _laserMovement;
};

__END_API

#endif
