/**
 * @file CollisionDetector.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "Spaceship.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Player.h"
#include "Direction.h"
#include "traits.h"
#include <vector>

__BEGIN_API

class CollisionDetector {

  public:
    CollisionDetector();
    ~CollisionDetector();

    bool checkSpaceshipCollision(Point protectile_center, int projectile_size, Point spaceship_center, int spaceship_size);
    void checkPlayerCollision();
    void checkEnemyCollision();

    void checkAllBoundaryCollision();
    dir::direction checkBoundaryCollision(Point center, int size);

    void addEnemy(Enemy* enemy);
    void addPlayer(Player* player);

    void removeEnemy(Enemy* enemy);
    void removePlayer();

  protected:
    Player * _player;
    std::vector<Enemy*> _enemies;
    int _width;
    int _height;

};

__END_API

#endif
