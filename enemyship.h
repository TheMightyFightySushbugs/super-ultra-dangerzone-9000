#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "gameobject.h"

class EnemyShip : public Bullet;
{
    private:
        static std::vector<Bullet*> enemyBullets;
    public:
        EnemyShip(int _positionX, int _positionY, QBrush _color);
        static int shot(GameObject & target);
        static void moveBullets();
        static void drawBullets(QPainter *painter);
};

#endif // ENEMYSHIP_H
