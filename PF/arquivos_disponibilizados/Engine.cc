#include "Engine.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdexcept>
#include <iostream>

#include "Timer.h"

__BEGIN_API

Window * Engine::_window;
Background * Engine::_background;
std::vector<NormalEnemy *> Engine::_enemies;
Player * Engine::_player = NULL;
Boss * Engine::_boss = NULL;
Input * Engine::_input;
Spawner * Engine::_spawner;
CollisionDetector * Engine::_collisionDetector;
Mine * Engine::_mine = NULL;
ALLEGRO_EVENT_QUEUE * Engine::_eventQueue = NULL;
bool Engine::_finish = false;
ALLEGRO_TIMER * Engine::_timer = NULL;
int Engine::_fps = 60;
int Engine::_displayHeight = 600;
int Engine::_displayWidth = 800;
ALLEGRO_DISPLAY * Engine::_display;
float Engine::_prevTime = 0;
float Engine::_dt = 0;
float Engine::_crtTime = 0;
bool Engine::_redraw = true;

Engine::Engine() {  }

Engine::~Engine() {
   if (_timer != NULL) al_destroy_timer(_timer);
   if (_eventQueue != NULL) al_destroy_event_queue(_eventQueue);
   if (_display != NULL) al_destroy_display(_display);
}

void Engine::init(void * name) {
   new Thread(run);
   new Thread(draw);
   new Thread(spawn);
   new Thread(input);
   new Thread(collision);
   new Thread(player);
   new Thread(boss);

   al_init();

   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();

   if ((_timer = al_create_timer(1.0 / _fps)) == NULL) {
      std::cout << "Unable to create game timer. Exiting.\n";
      exit(1);
   }

   if ((_eventQueue = al_create_event_queue()) == NULL) {
      std::cout << "Unable to create game event queue. Exiting.\n";
      exit(1);
   }

   _window = new Window(_eventQueue);
   _collisionDetector = new CollisionDetector();

   _background = new Background();
   _window->addBackground(_background);
   _spawner = new Spawner();
   _player = _spawner->spawnPlayer();
   _window->addSpaceship(_player);
   _collisionDetector->addPlayer(_player);

   _input = new Input(_player, _eventQueue);

   al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
   al_start_timer(_timer);

   loadSprites();

   run();
}


void Engine::run() {
   while (!_finish) {
      ALLEGRO_EVENT event;

      al_wait_for_event(_eventQueue, &event);

      if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         _finish = true;
         return;
      }

      if (event.type == ALLEGRO_EVENT_TIMER) {
         _crtTime = al_current_time();
         _dt = _crtTime - _prevTime;
         update(_dt);
         _redraw = true;
         _prevTime = _crtTime;
      }

      Thread::yield();
   }
}

void Engine::update(double dt) {
   st::state status;
   for (auto enemy = _enemies.begin(); enemy != _enemies.end(); ++enemy) {
      status = (*enemy)->run(dt);
      if (status == st::DEAD) {
         _collisionDetector->removeEnemy(*enemy);
         _window->removeSpaceship(*enemy);
      }
   }

   if (_mine) {
      status = _mine->run(dt);
      if (status == st::DEAD) {
         _collisionDetector->removeEnemy(_mine);
         _window->removeSpaceship(_mine);
         delete _mine;
         _mine = NULL;
      }
   }

   _background->update(dt);
}

void Engine::loadSprites()
{
   _window->loadSprites();
}

void Engine::collision() {
   while (!_finish) {
      _collisionDetector->checkEnemyCollision();
      _collisionDetector->checkPlayerCollision();
      _collisionDetector->checkAllBoundaryCollision();
      Thread::yield();
   }
}

void Engine::draw() {
   while (!_finish) {
      if (_redraw) {
         _window->draw();
         _player->drawLife();
         _redraw = false;
         al_flip_display();
      }
      Thread::yield();
   }
}

void Engine::input() {
   while (!_finish) {
      bool quitGame = _input->checkKeyDown();
      if (quitGame) _finish = true;
      Thread::yield();
   }
}

void Engine::spawn() {
   while (!_finish) {
      std::vector<NormalEnemy*> enemies = _spawner->spawnNormalEnemies();
      if (enemies.size() > 0) {
         for (std::vector<NormalEnemy *>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy) {
            _window->addSpaceship(*enemy);
            _collisionDetector->addEnemy(*enemy);
         }
         for (std::vector<NormalEnemy *>::iterator enemyToRemove = _enemies.begin(); enemyToRemove != _enemies.end(); ++enemyToRemove) {
            delete (*enemyToRemove);
         }
         _enemies = enemies;
      }

      if (!_mine) {
         _mine = _spawner->spawnMine();
         if (_mine) {
            _window->addSpaceship(_mine);
            _collisionDetector->addEnemy(_mine);
         }
      }

      if (!_boss) {
         _boss = _spawner->spawnBoss(_player);
         if (_boss) {
            _window->addSpaceship(_boss);
            _collisionDetector->addEnemy(_boss);
         }
      }

      Thread::yield();
   }
}

void Engine::player() {
   st::state status;
   while (!_finish) {
      if (_player) {
         status = _player->run(_dt);
         if (status == st::DEAD) {
            _collisionDetector->removePlayer();
            _window->removeSpaceship(_player);
            delete _player;
            delete _input;
            _input = NULL;
            _player = NULL;
            _finish = true;
         }
      }
      Thread::yield();
   }
}

void Engine::boss() {
   st::state status;
   while (!_finish) {
      if (_boss) {
         status = _boss->run(_dt);
         if (status == st::DEAD) {
            _collisionDetector->removeEnemy(_boss);
            _window->removeSpaceship(_boss);
            delete _boss;
            _boss = NULL;
         }
      }
      Thread::yield();
   }
}

__END_API
