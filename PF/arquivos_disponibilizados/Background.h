/**
 * @file Background.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <memory>
#include "Sprite.h"
#include "Point.h"
#include "Vector.h"
#include "traits.h"

__BEGIN_API

class Background {

  public:
    Background();
    ~Background() {  };

    void draw();

    void loadSprites();

    void update(double dt);

  protected:
    std::shared_ptr<Sprite> _bg;

    int _bgMaxXPosition;
    Point _bgPoint;
    Vector _bgMovement;

};

__END_API

#endif
