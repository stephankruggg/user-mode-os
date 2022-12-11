/**
 * @file Input.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Input.h"

__BEGIN_API

Input::Input(Player * player, ALLEGRO_EVENT_QUEUE * eventQueue) {
  if (!al_install_keyboard()) {
      std::cerr << "Unable to install keyboard. Exiting.\n";
      exit(1);
   }

  al_register_event_source(eventQueue, al_get_keyboard_event_source());

  _player = player;
}

bool Input::checkKeyDown() {
  al_get_keyboard_state(&_kb);

  if (al_key_down(&_kb, ALLEGRO_KEY_UP)) {
    _player->move_up();
  }

  if (al_key_down(&_kb, ALLEGRO_KEY_RIGHT)) {
    _player->move_right();
  }

  if (al_key_down(&_kb, ALLEGRO_KEY_DOWN)) {
    _player->move_down();
  }

  if (al_key_down(&_kb, ALLEGRO_KEY_LEFT)) {
    _player->move_left();
  }

  if (al_key_down(&_kb, ALLEGRO_KEY_1)) {
    _player->shootM();
  }

  if (al_key_down(&_kb, ALLEGRO_KEY_SPACE)) {
    _player->shootL();
  }

  if (al_key_down(&_kb, ALLEGRO_KEY_ESCAPE)) {
     return true;
  }

  return false;
}

__END_API
