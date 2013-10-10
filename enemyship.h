#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "gameobject.h"

class EnemyShip : public GameObject
{
    public:
        EnemyShip(int _positionX, int _positionY, QBrush _color);
};

#endif // ENEMYSHIP_H
