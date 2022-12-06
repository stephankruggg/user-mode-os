/**
 * @file Window.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef WINDOW_H
#define WINDOW_H

#include <allegro5/allegro.h>
#include <vector>
#include "Spaceship.h"
#include "Projectile.h"
#include "Background.h"

class Window {

  public:
    Window(ALLEGRO_EVENT_QUEUE * eventQueue);
    ~Window();

    void draw();
    void drawBackground();
    void drawSpaceshipsAndProjectiles();

    void addBackground(Background * background);
    void addSpaceship(Spaceship * spaceship);

    void removeSpaceship(Spaceship * spaceship);
    void removeBackground();

    void loadSprites();

  protected:
    ALLEGRO_DISPLAY *_display;
    int _displayWidth;
    int _displayHeight;

    Background * _background;

    std::vector<Spaceship *> _spaceships;
};

#endif
