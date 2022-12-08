/**
 * @file Spawner.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef SPAWNER_H
#define SPAWNER_H

#include "Boss.h"
#include "NormalEnemy.h"
#include "Player.h"
#include "Timer.h"
#include <vector>
#include "traits.h"

__BEGIN_API

class Spawner {

  public:
    Spawner();
    ~Spawner();

    Player * spawnPlayer();

    Boss * spawnBoss();
    std::vector<NormalEnemy*> spawnNormalEnemies();

    void spawnMine();

  protected:
    Point _playerPosition;
    int _playerSize;
    int _playerSpeed;
    int _playerMaxLife;
    ALLEGRO_COLOR _playerMissileColor;
    ALLEGRO_COLOR _playerLaserColor;
    int _playerMissileDelay;
    int _playerLaserDelay;

    Point _bossPosition;
    int _bossSize;
    ALLEGRO_COLOR _bossColor;
    int _bossSpeed;
    int _bossMaxLife;
    ALLEGRO_COLOR _bossMissileColor;
    ALLEGRO_COLOR _bossLaserColor;
    int _bossMissileDelay;
    int _bossLaserDelay;

    int _normalEnemyNumber;
    std::vector<Point> _normalEnemyPosition;
    int _normalEnemySize;
    ALLEGRO_COLOR _normalEnemyColor;
    int _normalEnemySpeed;
    int _normalEnemyMaxLife;
    ALLEGRO_COLOR _normalEnemyMissileColor;
    ALLEGRO_COLOR _normalEnemyLaserColor;
    int _normalEnemyMissileDelay;
    int _normalEnemyLaserDelay;
    
    std::shared_ptr<Timer> _timer;
    bool _respawn;
};

__END_API

#endif
