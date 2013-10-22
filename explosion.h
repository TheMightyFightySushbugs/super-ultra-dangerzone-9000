#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"

class Explosion : public GameObject
{
    public:
        Explosion(int _positionX, int _positionY, int _radius, QBrush &_color);
        void draw(QPainter *painter);
        ~Explosion() {};
};

#endif // EXPLOSION_H
