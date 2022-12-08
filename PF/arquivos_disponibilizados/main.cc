/**
 * @file main.cc
 * @brief
 * 
 */


#include <allegro5/allegro.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include "system.h"
#include "Engine.h"

__USING_API

int main() {
   System::init(Engine::init);


   return 0;
}
