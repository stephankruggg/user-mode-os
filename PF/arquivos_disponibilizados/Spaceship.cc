/**
 * @file Spaceship.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Spaceship.h"

__BEGIN_API

Spaceship::Spaceship(int size, double speed, int maxLife, Point position, ALLEGRO_COLOR missileColor, ALLEGRO_COLOR laserColor, double missileDelay, double laserDelay, double hitDelay) {
  reset_movement();
  _center = position;
  _size = size;
  _speed = speed;
  _maxLife = maxLife;
  _life = _maxLife;
  _missileColor = missileColor;
  _laserColor = laserColor;
  _missileDelay = missileDelay;
  _laserDelay = laserDelay;
  _hitDelay = hitDelay;
  _hitTimer = std::make_shared<Timer> (1);
  _missileTimer = std::make_shared<Timer> (1);
  _laserTimer = std::make_shared<Timer> (2);
  _hitTimer->create();
  _missileTimer->create();
  _laserTimer->create();
  _currentState = st::ALIVE;
}

void Spaceship::update(double dt) {
  _center = _center + _movement * dt;
  updateLasers(dt);
  updateMissiles(dt);
  resetTimers();
}

void Spaceship::reset_movement() {
  _movement = Vector(0, 0);
}

void Spaceship::move_down() {
  _movement.y += _speed;
}

void Spaceship::move_up() {
  _movement.y -= _speed;
}

void Spaceship::move_right() {
  _movement.x += _speed;
}

void Spaceship::move_left() {
  _movement.x -= _speed;
}

void Spaceship::shootLasers(std::vector<double> angles, std::vector<Vector> movements) {
  if (!_laserTimer->isRunning()) {
    for (std::size_t i = 0; i < angles.size(); ++i) {
      _laserTimer->startTimer();
      Laser * laser = new Laser(_center, _laserColor, movements[i], angles[i]);
      _currentLasers.push_back(laser);
    }
  }
}

void Spaceship::shootMissiles(std::vector<double> angles, std::vector<Vector> movements) {
  if (!_missileTimer->isRunning()) {
    for (std::size_t i = 0; i < angles.size(); ++i) {
      _missileTimer->startTimer();
      Missile * missile = new Missile(_center, _missileColor, movements[i], angles[i]);
      _currentMissiles.push_back(missile);
    }
  }
}

void Spaceship::take_hit() {
  if (!_hitTimer->isRunning()) {
    _hitTimer->startTimer();
    _life--;
  }
}

Point Spaceship::get_center() {
  return _center;
}

int Spaceship::get_size() {
  return _size;
}

void Spaceship::die() {
  _currentState = st::DEAD;
}

void Spaceship::drawDead() {
  if (_deathAnimationFrame < 5) deathAnimation();
  else die();
}

void Spaceship::deathAnimation() {
  _spriteDeath->draw_death_anim(_deathAnimationFrame, _center, 0);
  _deathAnimationFrame++;
}

std::vector<Laser*> Spaceship::getCurrentLasers() {
  return _currentLasers;
}

std::vector<Missile*> Spaceship::getCurrentMissiles() {
  return _currentMissiles;
}

void Spaceship::updateLasers(double dt) {
  for (std::vector<Laser *>::iterator itL = _currentLasers.begin(); itL != _currentLasers.end(); itL++) {
    (*itL)->update(dt);
  }
}

void Spaceship::updateMissiles(double dt) {
  for (std::vector<Missile *>::iterator itM = _currentMissiles.begin(); itM != _currentMissiles.end(); itM++) {
    (*itM)->update(dt);
  }
}

void Spaceship::resetTimers() {
  if (_laserTimer->getCount() >= _laserDelay) {
    _laserTimer->stopTimer(); 
    _laserTimer->resetCount();
  }

  if (_missileTimer->getCount() >= _missileDelay) {
    _missileTimer->resetCount();
    _missileTimer->stopTimer();
  }

  if (_hitTimer->getCount() >= _hitDelay) {
    _hitTimer->resetCount();
    _hitTimer->stopTimer();
  }
}

void Spaceship::laserCollision(Laser * laser) {
  std::vector<Laser*>::iterator iter = _currentLasers.begin();
  while (iter != _currentLasers.end())
  {
    if (*iter == laser)
    {
        iter = _currentLasers.erase(iter);
        delete laser;
        break;
    }
    iter++;
  }
}

void Spaceship::missileCollision(Missile * missile) {
  std::vector<Missile*>::iterator iter = _currentMissiles.begin();
  while (iter != _currentMissiles.end())
  {
    if (*iter == missile)
    {
        iter = _currentMissiles.erase(iter);
        delete missile;
        break;
    }
    iter++;
  }
}

Point Spaceship::getPosition() {
  return _center;
}

__END_API
