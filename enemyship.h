#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "gameobject.h"
#include "bullet.h"

class EnemyShip : public GameObject
{
    private:
        int health;
        static std::vector<Bullet*> enemyBullets;
    public:
        EnemyShip(int _positionX, int _positionY, QBrush _color);
        static int shot(GameObject & target);
        virtual bool move()=0;
        virtual bool inflictDamage(int damage);
        static void moveBullets();
        static void drawBullets(QPainter *painter);
        virtual ~EnemyShip() {};
};

#endif // ENEMYSHIP_H
