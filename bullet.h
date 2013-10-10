#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"

class Bullet : public GameObject
{
    public:
        Bullet(int _positionX, int _positionY, QBrush _color);
        virtual bool move()=0;
        virtual ~Bullet() {};
};

#endif // BULLET_H
