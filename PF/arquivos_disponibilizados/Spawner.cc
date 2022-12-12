/**
 * @file Spawner.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Spawner.h"

__BEGIN_API

const int PLAYER_SIZE = 50;
const Point PLAYER_POSITION = Point(200, 300);
const double PLAYER_SPEED = 250;
const int PLAYER_MAX_LIFE = 3;
const ALLEGRO_COLOR PLAYER_MISSILE_COLOR = al_map_rgb(0, 155, 0);
const ALLEGRO_COLOR PLAYER_LASER_COLOR = al_map_rgb(0, 155, 0);
const double PLAYER_MISSILE_DELAY = 2;
const double PLAYER_LASER_DELAY = 1;
const double PLAYER_HIT_DELAY = 2;

const ALLEGRO_COLOR BOSS_COLOR = al_map_rgb(155, 0, 0);
const int BOSS_SIZE = 400;
const Point BOSS_POSITION = Point(850, 300);
const double BOSS_SPEED = 1;
const int BOSS_MAX_LIFE = 50;
const ALLEGRO_COLOR BOSS_MISSILE_COLOR = al_map_rgb(155, 0, 0);
const ALLEGRO_COLOR BOSS_LASER_COLOR = al_map_rgb(155, 0, 0);
const double BOSS_MISSILE_DELAY = 2;
const double BOSS_LASER_DELAY = 6;
const double BOSS_HIT_DELAY = 1;

const ALLEGRO_COLOR NORMAL_ENEMY_COLOR = al_map_rgb(246, 64, 234);
const int NORMAL_ENEMY_SIZE = 40;
const std::vector<Point> NORMAL_ENEMY_POSITION = {Point(800, 300), Point(900, 350), Point(900, 250), Point(1000, 400), Point(1000, 200), Point(1100, 450), Point(1100, 150)};
const double NORMAL_ENEMY_SPEED = 0.5;
const int NORMAL_ENEMY_MAX_LIFE = 1;
const int NORMAL_ENEMY_NUMBER = 7;
const ALLEGRO_COLOR NORMAL_ENEMY_MISSILE_COLOR = al_map_rgb(0, 0, 155);
const ALLEGRO_COLOR NORMAL_ENEMY_LASER_COLOR = al_map_rgb(0, 0, 155);
const double NORMAL_ENEMY_MISSILE_DELAY = 3;
const double NORMAL_ENEMY_LASER_DELAY = 6;
const double NORMAL_ENEMY_HIT_DELAY = 0;

const ALLEGRO_COLOR MINE_COLOR = al_map_rgb(0, 0, 155);
const int MINE_SIZE = 40;
const Point MINE_POSITION = Point(850, 300);
const double MINE_SPEED = 1;
const int MINE_MAX_LIFE = 1;
const ALLEGRO_COLOR MINE_MISSILE_COLOR = al_map_rgb(155, 0, 0);
const ALLEGRO_COLOR MINE_LASER_COLOR = al_map_rgb(155, 0, 0);
const double MINE_MISSILE_DELAY = 1;
const double MINE_LASER_DELAY = 1;
const double MINE_HIT_DELAY = 0;

Spawner::Spawner() {
  _timer = std::make_shared<Timer> (1);
  _timer->create();
  _respawn = true;
  _mineRespawn = true;
}

Player * Spawner::spawnPlayer() {
  _timer->startTimer();
  return new Player(PLAYER_SIZE, PLAYER_SPEED, PLAYER_MAX_LIFE, PLAYER_POSITION, PLAYER_MISSILE_COLOR, PLAYER_LASER_COLOR, PLAYER_MISSILE_DELAY, PLAYER_LASER_DELAY, PLAYER_HIT_DELAY);
}

Boss * Spawner::spawnBoss(Player * player) {
  if (_timer->getCount() == 60) {
    _respawn = false;
    _timer->resetCount();
    return new Boss(BOSS_COLOR, BOSS_SIZE, BOSS_SPEED, BOSS_MAX_LIFE, BOSS_POSITION, BOSS_MISSILE_COLOR, BOSS_LASER_COLOR, BOSS_MISSILE_DELAY, BOSS_LASER_DELAY, player, BOSS_HIT_DELAY);
  }
}

std::vector<NormalEnemy*> Spawner::spawnNormalEnemies() {
  std::vector<NormalEnemy*> normalEnemies;
  if (_respawn && _timer->getCount() % 10 == 0) {
    _respawn = false;
    for (int i = 0; i < NORMAL_ENEMY_NUMBER; i++) {
      normalEnemies.push_back(new NormalEnemy(NORMAL_ENEMY_COLOR, NORMAL_ENEMY_SIZE, NORMAL_ENEMY_SPEED, NORMAL_ENEMY_MAX_LIFE, NORMAL_ENEMY_POSITION[i], NORMAL_ENEMY_MISSILE_COLOR, NORMAL_ENEMY_LASER_COLOR, NORMAL_ENEMY_MISSILE_DELAY, NORMAL_ENEMY_LASER_DELAY, NORMAL_ENEMY_HIT_DELAY));
    }
  }

  if (_timer->getCount() % 10 != 0) _respawn = true;

  return normalEnemies;
}

Mine * Spawner::spawnMine() {
  if (_mineRespawn && _timer->getCount() % 30 == 0 && _timer->getCount() > 0) {
    _mineRespawn = false;
    return new Mine(MINE_COLOR, MINE_SIZE, MINE_SPEED, MINE_MAX_LIFE, MINE_POSITION, MINE_MISSILE_COLOR, MINE_LASER_COLOR, MINE_MISSILE_DELAY, MINE_LASER_DELAY, MINE_HIT_DELAY);
  }

  if (_timer->getCount() % 10 != 0) _mineRespawn = true;
  return NULL;
}

__END_API
