/**
 * @file Input.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro.h>
#include "Player.h"
#include <map>
#include <iostream>
#include <functional>
#include "traits.h"

__BEGIN_API

class Input {

  public:
    Input(Player * player, ALLEGRO_EVENT_QUEUE * eventQueue);
    ~Input() {  };

    bool checkKeyDown();

  protected:
    ALLEGRO_EVENT_QUEUE *_eventQueue;
    ALLEGRO_KEYBOARD_STATE _kb;
    Player * _player;

};

__END_API

#endif
