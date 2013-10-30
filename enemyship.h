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
        unsigned int health, pointValue;
    public:
        EnemyShip(int _positionX, int _positionY, unsigned int _health,
                  unsigned int _pointValue, QBrush &_color);

        //Checks to see if any enemy bullets are colliding with 'target' and computes the
        //combined damage they inflict. This sum makes up the return value's lower 28 bits.
        //The upper four bits are used to indicate which players' shots caused that damage
        //(If the nth most significant bit is 1, then player n was responsible for the
        //damage; this way, damage from multiple bullets and from multiple players can be
        //tracked simultaneously). If no bullets collided with 'target', then the return
        //value is just zero.
        static unsigned int shot(GameObject & target);

        //This function is called once per frame for each instance of EnemyShip. It's a purely
        //virtual function, meaning that every class of EnemyShip must define its own version
        //of move(). (The reasoning behind this is that every class of ship will follow its own
        //specific movement patterns) The function must return 'true' when the ship exits the
        //screen and 'false' otherwise (so that the game may know when to delete ship).
        virtual bool move()=0;

        //This function inflicts '_damage' amount of damage upon the ship. If this was enough
        //to destroy the ship, the function returns the ship's point value (including the
        //corresponding player ID bits to indicate which player(s) is/are responsible),
        //otherwise 0. This version of inflictDamage() is good enough for most enemies, but
        //bosses and more complex EnemyShips should implement their own versions (which will
        //allow them to implement periods of vulenrability/invulnerability)
        virtual unsigned int inflictDamage(unsigned int _damage);

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
