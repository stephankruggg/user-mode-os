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
#include "thread.h"
#include "cpu.h"
#include "traits.h"
#include "semaphore.h"

__BEGIN_API

class Engine {
      
  public:
   Engine();
   ~Engine();
   
   static void init(void * name);
   static void run();
   static void update(double dt);

   inline int getWidth() const {
      return _displayWidth;
   }
   inline int getHeight() const {
      return _displayHeight;
   }
   inline int getFps() const {
      return _fps;
   }

   static void collision();
   static void spawn();
   static void draw();
   static void input();
   static void player();
   static void boss();

   static void removeEnemy(NormalEnemy * enemy);

  protected:
   static Window * _window;
   static Background * _background;
   static std::vector<NormalEnemy *> _enemies;
   static Player * _player;
   static Boss * _boss;
   static Input * _input;
   static Spawner * _spawner;
   static CollisionDetector * _collisionDetector;
   static Mine * _mine;

   static Thread * _threadRun;
   static Thread * _threadDraw;
   static Thread * _threadSpawn;
   static Thread * _threadInput;
   static Thread * _threadCollision;
   static Thread * _threadPlayer;
   static Thread * _threadBoss;

   static void loadSprites();

   static int _displayWidth;
   static int _displayHeight;
   static int _fps;

   static ALLEGRO_TIMER *_timer;
   static ALLEGRO_EVENT_QUEUE *_eventQueue;
   static ALLEGRO_DISPLAY *_display;

   static bool _finish;
   static double _prevTime;
   static double _dt;
   static double _crtTime;
   static bool _redraw;

};

__END_API

#endif
