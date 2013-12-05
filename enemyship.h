#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "gameobject.h"
#include "bullet.h"
#include "explosion.h"
#include <QPainter>

/*! \brief An abstract class used to represent an enemy ship
 */
class EnemyShip : public GameObject
{
    protected:
        static std::list<Bullet*> enemyBullets;
        unsigned int health, pointValue;
        bool flash;
    public:
        /**
         * Constructor for EnemyShip
         *
         * @param _positionX Enemy's initial X coordinate
         * @param _positionY Enemy's initial Y coordinate
         * @param _health How much damage this enemy can take before exploding
         * @param _width How many units wide this enemy is
         * @param _height How many units high this enemy is
         * @param _pointValue How much points a playes wins for defeating this enemy
         * @param _color What color this enemy is
         */
        EnemyShip(int _positionX, int _positionY, unsigned int _health, int _width, int _height,
                  unsigned int _pointValue, QBrush &_color);

        /**
         * Checks to see if any enemy bullets are colliding with 'target' and computes the
         * combined damage they inflict.
         *
         * @param target The GameObject we're testing against
         * @return If no bullets collided with 'target', then the return value is just zero.
         *         If 'target' was hit, though, The sum of the damage inflicted makes up the
         *         return value's lower 28 bits. The upper four bits are used to indicate
         *         which players' shots caused that damage (If the nth most significant bit
         *         is 1, then player n was responsible for the damage; this way, damage from
         *         multiple bullets and from multiple players can be tracked simultaneously).
         */
        static unsigned int shot(GameObject & target);


        /**
         * Make the enemy do whatever it's supposed to do, then updates its X & Y coordinates.
         * This function is called once per frame for each instance of EnemyShip. It's a purely
         * virtual function, meaning that every class of EnemyShip must define its own version
         * of move(). (The reasoning behind this is that every class of ship will follow its
         * own specific movement patterns)
         *
         * @return true if the enemy has moved out of bounds, false otherwise
         */
        virtual bool move()=0;

        /**
         * Inflicts '_damage' amount of damage upon this enemy. This version of inflictDamage()
         * is good enough for most enemies, but bosses and more complex EnemyShips should
         * implement their own versions (which will allow them to implement periods of
         * vulenrability/invulnerability)
         *
         * @param _damage How much damage to inflict (along with the corresponding player ID bits)
         * @return the ship's point value (including the corresponding player ID bits to
         *         indicate which player(s) is/are responsible) if the damage inflicted was
         *         enough to destroy it. Otherwise 0.
         */
        virtual unsigned int inflictDamage(unsigned int _damage);

        /**
         * Moves all enemy bullet & updates their X & Y coordinates
         */
        static void moveBullets();

        /**
         * Draws every enemy bullet
         * @param painter A QPainter object with which to paint
         */
        static void drawBullets(QPainter *painter);
        static void cleanUpEnemyBullets();
        virtual ~EnemyShip() {}
};

/*! \brief An enemy type that just moves in a straight, horizontal line
 */
class DummyShip : public EnemyShip
{
    private:
        static QBrush dummyColor;
    public:
        /**
         * Constructor for DummyShip
         * @param _positionY DummyShip's initial Y position
         */
        DummyShip(int _positionY);

        /**
         * Make DummyShip do whatever it's supposed to do, then updates its X & Y coordinates.
         *
         * @return true if DummyShip has moved out of bounds, false otherwise
         */
        bool move();

        /**
         * Draws this instance of DummyShip onto the window
         * @param painter A QPainter object with which to paint
         */
        void draw(QPainter *painter);
        ~DummyShip() {}
};

/*! \brief An enemy type that moves horizontally in a zig-zag pattern. It fires bullets at
 *         the apex of its zig-zags.
 */
class ZigZagShip : public EnemyShip
{
    private:
        static QBrush zigZagColor;
        int timer;
        bool movingUp;
    public:
        /**
         * Constructor for ZigZagShip
         * @param _positionY ZigZagShip's initial Y position
         */
        ZigZagShip(int _positionY);

        /**
         * Make ZigZagShip do whatever it's supposed to do, then updates its X & Y coordinates.
         *
         * @return true if ZigZagShip has moved out of bounds, false otherwise
         */
        bool move();

        /**
         * Draws this instance of ZigZagShip onto the window
         * @param painter A QPainter object with which to paint
         */
        void draw(QPainter *painter);
        ~ZigZagShip() {}
};

/*! \brief An enemy type that moves over the entire screen in a figure-eight pattern. It fires
 *         bullets at a fixed interval and spawns an endless supply of DummyShips from the
 *         right side of the screen.
 */
class SpawnerShip : public EnemyShip
{
    private:
        static QBrush spawnerColor;
        int timerX, timerY, velocityX, velocityY;
        bool movingUp, movingLeft;
    public:
        /**
         * Constructor for SpawnerShip
         * @param _positionY SpawnerShip's initial Y position
         */
        SpawnerShip(int _positionY);

        /**
         * Make SpawnerShip do whatever it's supposed to do, then updates its X & Y coordinates.
         *
         * @return true if SpawnerShip has moved out of bounds, false otherwise
         */
        bool move();

        /**
         * Draws this instance of SpawnerShip onto the window
         * @param painter A QPainter object with which to paint
         */
        void draw(QPainter *painter);
        unsigned int inflictDamage(unsigned int _damage);
        ~SpawnerShip() {}
};

/*! \brief A bigger version of DummyShip with more health
 */
class StraightShip : public EnemyShip
{
    private:
        static QBrush StraightShipColor;
    public:
        /**
         * Constructor for StraightShip
         * @param _positionY StraightShip's initial Y position
         */
        StraightShip(int _positionY);

        /**
         * Make StraightShip do whatever it's supposed to do, then updates its X & Y coordinates.
         *
         * @return true if StraightShip has moved out of bounds, false otherwise
         */
        bool move();

        /**
         * Draws this instance of StraightShip onto the window
         * @param painter A QPainter object with which to paint
         */
        void draw(QPainter *painter);
        ~StraightShip() {}
};

/*! \brief An enemy type that moves diagonally (left & down)
 */
class DiverShip : public EnemyShip
{
    private:
        static QBrush diverShipColor;
    public:
        /**
         * Constructor for DiverShip
         * @param _positionY DiverShip's initial Y position
         */
        DiverShip(int _positionY);

        /**
         * Make DiverShip do whatever it's supposed to do, then updates its X & Y coordinates.
         *
         * @return true if DiverShip has moved out of bounds, false otherwise
         */
        bool move();

        /**
         * Draws this instance of DiverShip onto the window
         * @param painter A QPainter object with which to paint
         */
        void draw(QPainter *painter);
        ~DiverShip() {}
};

/*! \brief An enemy type that moves diagonally (left & up)
 */
class RiserShip : public EnemyShip
{
    private:
        static QBrush riserShipColor;
    public:
        /**
         * Constructor for RiserShip
         * @param _positionY RiserShip's initial Y position
         */
        RiserShip(int _positionY);

        /**
         * Make RiserShip do whatever it's supposed to do, then updates its X & Y coordinates.
         *
         * @return true if RiserShip has moved out of bounds, false otherwise
         */
        bool move();

        /**
         * Draws this instance of RiserShip onto the window
         * @param painter A QPainter object with which to paint
         */
        void draw(QPainter *painter);
        ~RiserShip() {}
};

/*! \brief An enemy type that moves horizontally & pauses occasionally to shoot a pair of
 *         vertical bullets out of its sides.
 */
class SideShotShip : public EnemyShip
{
    private:
        static QBrush sideShotColor;
        bool shooting;
        int timer;
    public:
        /**
         * Constructor for SideShotShip
         * @param _positionY SideShotShip's initial Y position
         */
        SideShotShip(int _positionY);

        /**
         * Make SideShotShip do whatever it's supposed to do, then updates its X & Y coordinates.
         *
         * @return true if SideShotShip has moved out of bounds, false otherwise
         */
        bool move();

        /**
         * Draws this instance of SideShotShip onto the window
         * @param painter A QPainter object with which to paint
         */
        void draw(QPainter *painter);
        ~SideShotShip() {}
};

#endif // ENEMYSHIP_H
