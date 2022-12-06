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

Engine::Engine(int w, int h, int fps) : _displayWidth(w), _displayHeight(h), _fps(fps), _timer(NULL), _eventQueue(NULL), _finish(false) {  }

Engine::~Engine() {
   if (_timer != NULL) al_destroy_timer(_timer);
   if (_eventQueue != NULL) al_destroy_event_queue(_eventQueue);
   if (_display != NULL) al_destroy_display(_display);
}

void Engine::init() {
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
}


void Engine::run() {
   float prevTime = 0;

   while (!_finish) {
      gameLoop(prevTime);
   }
}

void Engine::gameLoop(float& prevTime) {
   ALLEGRO_EVENT event;

   bool redraw = true;
   float crtTime;
   
   _input->checkKeyDown();

   al_wait_for_event(_eventQueue, &event);

   if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      _finish = true;
      return;
   }

   if (event.type == ALLEGRO_EVENT_TIMER) {
      spawn();

      crtTime = al_current_time();
      update(crtTime - prevTime);
      prevTime = crtTime;
      redraw = true;

      checkCollision();
   }

   if (redraw && al_is_event_queue_empty(_eventQueue)) {
      redraw = false;
      _window->draw();
      al_flip_display();
   }
}

void Engine::update(double dt) {
   if (_player) _player->update(dt);

   if (_boss) _boss->run(dt);

   for (auto enemy = _enemies.begin(); enemy != _enemies.end(); ++enemy) {
      (*enemy)->run(dt);
   }

   _background->update(dt);
}

void Engine::loadSprites()
{
   _window->loadSprites();
}

void Engine::checkCollision() {
   _collisionDetector->checkEnemyCollision();
   _collisionDetector->checkPlayerCollision();
   _collisionDetector->checkAllBoundaryCollision();
}

void Engine::spawn() {
   if (!_boss) {
      _boss = _spawner->spawnBoss();
      if (_boss) {
         _window->addSpaceship(_boss);
         _collisionDetector->addEnemy(_boss);
      }
   }

   std::vector<NormalEnemy*> enemies = _spawner->spawnNormalEnemies();
   if (enemies.size() > 0) {
      for (std::vector<NormalEnemy *>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy) {
         _enemies.push_back(*enemy);
         _window->addSpaceship(*enemy);
         _collisionDetector->addEnemy(*enemy);
      }
   }
}
