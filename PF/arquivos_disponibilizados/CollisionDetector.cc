/**
 * @file CollisionDetector.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "CollisionDetector.h"

__BEGIN_API

CollisionDetector::CollisionDetector() {
  _width = 800;
  _height = 600;
}

bool CollisionDetector::checkSpaceshipCollision(Point projectile_center, int projectile_size, Point spaceship_center, int spaceship_size) {
  if ((projectile_center.x - projectile_size <= spaceship_center.x + spaceship_size || projectile_center.x + projectile_size <= spaceship_center.x + spaceship_size)
       && (projectile_center.x - projectile_size >= spaceship_center.x - spaceship_size || projectile_center.x + projectile_size >= spaceship_center.x - spaceship_size)) {
    return ((projectile_center.y - projectile_size <= spaceship_center.y + spaceship_size || projectile_center.y + projectile_size <= spaceship_center.y + spaceship_size)
             && (projectile_center.y - projectile_size >= spaceship_center.y - spaceship_size || projectile_center.y + projectile_size >= spaceship_center.y - spaceship_size));
  }
  return false;
}

void CollisionDetector::checkPlayerCollision() {
  int player_size = _player->get_size() / 2;
  Point player_center = _player->get_center();

  for (std::vector<Enemy*>::iterator enemy = _enemies.begin(); enemy != _enemies.end(); enemy++) {
    std::vector<Laser*> lasers = (*enemy)->getCurrentLasers();
    for (std::vector<Laser *>::iterator laser = lasers.begin(); laser != lasers.end(); laser++) {
      Point laser_center = (*laser)->get_center();
      int laser_size = (*laser)->get_size() / 2;

      if (checkSpaceshipCollision(laser_center, laser_size, player_center, player_size)) {
        (*enemy)->laserCollision(*laser);
        _player->take_hit();
      }
    }

    std::vector<Missile*> missiles = (*enemy)->getCurrentMissiles();
    for (std::vector<Laser *>::iterator missile = lasers.begin(); missile != lasers.end(); missile++) {
      Point missile_center = (*missile)->get_center();
      int missile_size = (*missile)->get_size() / 2;

      if (checkSpaceshipCollision(missile_center, missile_size, player_center, player_size)) {
        _player->take_hit();
      }
    }
  }
}

void CollisionDetector::checkEnemyCollision() {
  for (auto enemy = _enemies.begin(); enemy != _enemies.end(); ++enemy) {
    int enemy_size = (*enemy)->get_size() / 2;
    Point enemy_center = (*enemy)->get_center();

    std::vector<Laser*> lasers = _player->getCurrentLasers();
    for (std::vector<Laser *>::iterator laser = lasers.begin(); laser != lasers.end(); laser++) {
      Point laser_center = (*laser)->get_center();
      int laser_size = (*laser)->get_size() / 2;

      if (checkSpaceshipCollision(laser_center, laser_size, enemy_center, enemy_size)) {
        _player->laserCollision(*laser);
        (*enemy)->take_hit();
      }
    }

    std::vector<Missile*> missiles = _player->getCurrentMissiles();
    for (std::vector<Missile *>::iterator missile = missiles.begin(); missile != missiles.end(); missile++) {
      Point missile_center = (*missile)->get_center();
      int missile_size = (*missile)->get_size() / 2;

      if (checkSpaceshipCollision(missile_center, missile_size, enemy_center, enemy_size)) {
        (*enemy)->take_hit();
      }
    }
  }
}

void CollisionDetector::addEnemy(Enemy* enemy) {
  _enemies.push_back(enemy);
}

void CollisionDetector::addPlayer(Player* player) {
  _player = player;
}

void CollisionDetector::removeEnemy(Enemy* enemy) {
  std::vector<Enemy*>::iterator iter = _enemies.begin();
  while (iter != _enemies.end())
  {
    if (*iter == enemy)
    {
        iter = _enemies.erase(iter);
        break;
    }
    iter++;
  }
}

void CollisionDetector::removePlayer() {
  _player = NULL;
}

void CollisionDetector::checkAllBoundaryCollision() {
  for (auto enemy = _enemies.begin(); enemy != _enemies.end(); ++enemy) {

    std::vector<Laser*> lasers = _player->getCurrentLasers();
    for (std::vector<Laser *>::iterator laser = lasers.begin(); laser != lasers.end(); laser++) {
      Point laser_center = (*laser)->get_center();
      int laser_size = (*laser)->get_size() / 2;

      if (checkBoundaryCollision(laser_center, laser_size)) {
        (*enemy)->laserCollision(*laser);
      }
    }

    std::vector<Missile*> missiles = _player->getCurrentMissiles();
    for (std::vector<Missile *>::iterator missile = missiles.begin(); missile != missiles.end(); missile++) {
      Point missile_center = (*missile)->get_center();
      int missile_size = (*missile)->get_size() / 2;

      if (checkBoundaryCollision(missile_center, missile_size)) {
        (*enemy)->missileCollision(*missile);
      }
    }

    int enemy_size = (*enemy)->get_size() / 2;
    Point enemy_center = (*enemy)->get_center();
    
    dir::direction direc = checkBoundaryCollision(enemy_center, enemy_size);
    if (direc) {
      (*enemy)->boundaryCollision(direc);
    }
  }

  std::vector<Laser*> lasers = _player->getCurrentLasers();
  for (std::vector<Laser *>::iterator laser = lasers.begin(); laser != lasers.end(); laser++) {
    Point laser_center = (*laser)->get_center();
    int laser_size = (*laser)->get_size() / 2;

    if (checkBoundaryCollision(laser_center, laser_size)) {
      _player->laserCollision(*laser);
    }
  }

  std::vector<Missile*> missiles = _player->getCurrentMissiles();
  for (std::vector<Missile *>::iterator missile = missiles.begin(); missile != missiles.end(); missile++) {
    Point missile_center = (*missile)->get_center();
    int missile_size = (*missile)->get_size() / 2;

    if (checkBoundaryCollision(missile_center, missile_size)) {
      _player->missileCollision(*missile);
    }
  }

  int player_size = _player->get_size() / 2;
  Point player_center = _player->get_center();
  dir::direction direction = checkBoundaryCollision(player_center, player_size);
  if (direction) {
    _player->boundaryCollision(direction);
  }
}

dir::direction CollisionDetector::checkBoundaryCollision(Point center, int size) {
  if (center.x - size <= 0) return dir::LEFT;
  else if (center.x + size >= _width) return dir::RIGHT;

  if (center.y - size <= 0) return dir::UP;
  else if (center.y + size >= _height) return dir::DOWN;

  return dir::NONE;
}

__END_API
