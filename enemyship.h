#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "gameobject.h"
#include "bullet.h"
#include "explosion.h"
#include <QPainter>

class EnemyShip : public GameObject
{
    private:
        static std::vector<Bullet*> enemyBullets;
    protected:
        int health;
    public:
        EnemyShip(int _positionX, int _positionY, int _health, QBrush &_color);
        static int shot(GameObject & target);
        virtual bool move()=0;
        virtual bool inflictDamage(int _damage);
        static void moveBullets();
        static void drawBullets(QPainter *painter);
        virtual ~EnemyShip() {}
};

class DummyShip : public EnemyShip
{
    private:
        static QBrush dummyColor;
    public:
        DummyShip(int _positionX, int _positionY);
        bool move();
        void draw(QPainter *painter);
        ~DummyShip() {};
};

#endif // ENEMYSHIP_H
