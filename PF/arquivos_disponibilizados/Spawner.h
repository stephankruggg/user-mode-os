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
#include "Mine.h"
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
    Mine * spawnMine();

  protected:
    Point _playerPosition;
    int _playerSize;
    double _playerSpeed;
    int _playerMaxLife;
    ALLEGRO_COLOR _playerMissileColor;
    ALLEGRO_COLOR _playerLaserColor;
    double _playerMissileDelay;
    double _playerLaserDelay;

    Point _bossPosition;
    int _bossSize;
    ALLEGRO_COLOR _bossColor;
    double _bossSpeed;
    int _bossMaxLife;
    ALLEGRO_COLOR _bossMissileColor;
    ALLEGRO_COLOR _bossLaserColor;
    double _bossMissileDelay;
    double _bossLaserDelay;

    int _normalEnemyNumber;
    std::vector<Point> _normalEnemyPosition;
    int _normalEnemySize;
    ALLEGRO_COLOR _normalEnemyColor;
    double _normalEnemySpeed;
    int _normalEnemyMaxLife;
    ALLEGRO_COLOR _normalEnemyMissileColor;
    ALLEGRO_COLOR _normalEnemyLaserColor;
    double _normalEnemyMissileDelay;
    double _normalEnemyLaserDelay;

    Point _minePosition;
    int _mineSize;
    ALLEGRO_COLOR _mineColor;
    double _mineSpeed;
    int _mineMaxLife;
    ALLEGRO_COLOR _mineMissileColor;
    ALLEGRO_COLOR _mineLaserColor;
    double _mineMissileDelay;
    double _mineLaserDelay;
    
    std::shared_ptr<Timer> _timer;
    bool _respawn;
    bool _mineRespawn;
};

__END_API

#endif
