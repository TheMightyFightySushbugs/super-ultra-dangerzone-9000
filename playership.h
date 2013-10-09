#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "gameobject.h"

class PlayerShip : public GameObject
{
    private:
        static vector<Bullet> playerBullets;
    public:
        PlayerShip();
        void draw();
        void reset();
        void shoot();
        static int shot(GameObject & target);
};

#endif // PLAYERSHIP_H
