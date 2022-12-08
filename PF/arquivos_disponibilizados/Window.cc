/**
 * @file Window.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Window.h"

__BEGIN_API

Window::Window(ALLEGRO_EVENT_QUEUE * eventQueue) {
  _displayHeight = 600;
  _displayWidth = 800;

  if ((_display = al_create_display(_displayWidth, _displayHeight)) == NULL) {
    std::cout << "Unable to initialize the display. Exiting.\n";
    exit(1); 
  }

  al_register_event_source(eventQueue, al_get_display_event_source(_display)); 
}

void Window::draw() {
  drawBackground();
  drawSpaceshipsAndProjectiles();
}

void Window::drawSpaceshipsAndProjectiles() {
  for (std::vector<Spaceship *>::iterator it = _spaceships.begin(); it != _spaceships.end(); it++) {
    (*it)->draw();

    std::vector<Laser*> lasers = (*it)->getCurrentLasers();
    for (std::vector<Laser *>::iterator itL = lasers.begin(); itL != lasers.end(); itL++) {
      (*itL)->draw();
    }

    std::vector<Missile*> missiles = (*it)->getCurrentMissiles();
    for (std::vector<Missile *>::iterator itM = missiles.begin(); itM != missiles.end(); itM++) {
      (*itM)->draw();
    }
  }
}

void Window::drawBackground() {
  _background->draw();
}

void Window::loadSprites() {
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));

  _background->loadSprites();

  for (std::vector<Spaceship *>::iterator it = _spaceships.begin(); it != _spaceships.end(); it++) {
    (*it)->loadSprites();
  }

  al_destroy_path(path);
}

void Window::addBackground(Background * background) {
  _background = background;
}

void Window::addSpaceship(Spaceship * spaceship) {
  _spaceships.push_back(spaceship);
}

void Window::removeSpaceship(Spaceship * spaceship) {
  std::vector<Spaceship *>::iterator iter = _spaceships.begin();
  while (iter != _spaceships.end())
  {
    if (*iter == spaceship)
    {
        iter = _spaceships.erase(iter);
        break;
    }
    iter++;
  }
}

void Window::removeBackground() {
  _background = NULL;
}

__END_API
