#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"

class Bullet : public GameObject
{
    private:
        int damage;
    public:
        Bullet(int _positionX, int _positionY, QBrush _color);
        int getDamage() {return damage;}
        virtual bool move()=0;
        virtual ~Bullet() {};
};

#endif // BULLET_H
