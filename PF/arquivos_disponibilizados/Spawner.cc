/**
 * @file Spawner.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Spawner.h"

__BEGIN_API

Spawner::Spawner() {
  _playerSize = 40;
  _playerPosition = Point(200, 300);
  _playerSpeed = 250;
  _playerMaxLife = 30;
  _playerMissileColor = al_map_rgb(0, 155, 0);
  _playerLaserColor = al_map_rgb(0, 155, 0);
  _playerMissileDelay = 2;
  _playerLaserDelay = 1;

  _bossColor = al_map_rgb(155, 0, 0);
  _bossSize = 400;
  _bossSpeed = 1;
  _bossMaxLife = 100;
  _bossPosition = Point(850, 300);
  _bossMissileColor = al_map_rgb(155, 0, 0);
  _bossLaserColor = al_map_rgb(155, 0, 0);
  _bossMissileDelay = 2;
  _bossLaserDelay = 4;

  _normalEnemyColor = al_map_rgb(246, 64, 234);
  _normalEnemySize = 40;
  _normalEnemySpeed = 1;
  _normalEnemyMaxLife = 1;
  _normalEnemyNumber = 7;
  _normalEnemyPosition = {Point(800, 300), Point(900, 350), Point(900, 250), Point(1000, 400), Point(1000, 200), Point(1100, 450), Point(1100, 150)};
  _normalEnemyMissileColor = al_map_rgb(0, 0, 155);
  _normalEnemyLaserColor = al_map_rgb(0, 0, 155);
  _normalEnemyLaserDelay = 8;
  _normalEnemyMissileDelay = 3;

  _timer = std::make_shared<Timer> (1);
  _timer->create();
  _respawn = true;
}

Player * Spawner::spawnPlayer() {
  _timer->startTimer();
  return new Player(_playerSize, _playerSpeed, _playerMaxLife, _playerPosition, _playerMissileColor, _playerLaserColor, _playerMissileDelay, _playerLaserDelay);
}

Boss * Spawner::spawnBoss() {
  if (_timer->getCount() == 60) {
    _respawn = false;
    _timer->resetCount();
    return new Boss(_bossColor, _bossSize, _bossSpeed, _bossMaxLife, _bossPosition, _bossMissileColor, _bossLaserColor, _bossMissileDelay, _bossLaserDelay);
  }
}

std::vector<NormalEnemy*> Spawner::spawnNormalEnemies() {
  std::vector<NormalEnemy*> normalEnemies;
  if (_respawn && _timer->getCount() % 10 == 0) {
    _respawn = false;
    for (int i = 0; i < _normalEnemyNumber; i++) {
      normalEnemies.push_back(new NormalEnemy(_normalEnemyColor, _normalEnemySize, _normalEnemySpeed, _normalEnemyMaxLife, _normalEnemyPosition[i], _normalEnemyMissileColor, _normalEnemyLaserColor, _normalEnemyMissileDelay, _normalEnemyLaserDelay));
    }
  }

  if (_timer->getCount() % 10 != 0) _respawn = true;

  return normalEnemies;
}

__END_API
