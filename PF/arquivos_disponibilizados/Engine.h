/**
 * @file Engine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef ENGINE_H
#define ENGINE_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>

#include "Window.h"
#include "Player.h"
#include "Input.h"
#include "Spawner.h"
#include "CollisionDetector.h"

// forward declarations
class Menu;
class Root;

class Engine {
      
  public:
   Engine(int w, int h, int fps);
   ~Engine();
   
   void init();
   void run();
   void update(double dt);

   void gameLoop(float& prevTime);

   inline int getWidth() const {
      return _displayWidth;
   }
   inline int getHeight() const {
      return _displayHeight;
   }
   inline int getFps() const {
      return _fps;
   }

   void checkCollision();
   void spawn();

  protected:
   Window * _window;
   Background * _background;
   std::vector<NormalEnemy *> _enemies;
   Player * _player = NULL;
   Boss * _boss = NULL;
   Input * _input;
   Spawner * _spawner;
   CollisionDetector * _collisionDetector;

   void loadSprites();

   int _displayWidth;
   int _displayHeight;
   int _fps;

   ALLEGRO_TIMER *_timer;
   ALLEGRO_EVENT_QUEUE *_eventQueue;
   ALLEGRO_DISPLAY *_display;

   bool _finish;
   
};





#endif
