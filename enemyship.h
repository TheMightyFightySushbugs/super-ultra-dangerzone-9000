#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "gameobject.h"
#include "bullet.h"
#include "explosion.h"
#include <QPainter>

class EnemyShip : public GameObject
{
    private:
        static std::list<Bullet*> enemyBullets;
    protected:
        int health, pointValue;
    public:
        EnemyShip(int _positionX, int _positionY, int _health, int _pointValue, QBrush &_color);

        //Checks to see if any enemy bullets are colliding with 'target' and computes the
        //combined damage they inflict. This sum is the return value (If no bullets collided
        //with 'target', then the return value is just zero).
        static int shot(GameObject & target);

        //This function is called once per frame for each instance of EnemyShip. It's a purely
        //virtual function, meaning that every class of EnemyShip must define its own version
        //of move(). (The reasoning behind this is that every class of ship will follow its own
        //specific movement patterns) The function must return 'true' when the ship exits the
        //screen and 'false' otherwise (so that the game may know when to delete ship).
        virtual bool move()=0;

        //This function inflicts '_damage' amount of damage upon the ship. If this was enough
        //to destroy the ship, the function returns the ship's point value, otherwise 0. This
        //version of inflictDamage() is good enough for most enemies, but bosses and more complex
        //EnemyShips should implement their own versions (which will allow them to implement
        //periods of vulenrability/invulnerability)
        virtual int inflictDamage(int _damage);

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
        ~DummyShip() {}
};

#endif // ENEMYSHIP_H
