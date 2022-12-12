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
    ~Spawner() {  };

    Player * spawnPlayer();

    Boss * spawnBoss(Player * player);
    std::vector<NormalEnemy*> spawnNormalEnemies();
    Mine * spawnMine();

  protected:
    std::shared_ptr<Timer> _timer;
    bool _respawn;
    bool _mineRespawn;
};

__END_API

#endif
