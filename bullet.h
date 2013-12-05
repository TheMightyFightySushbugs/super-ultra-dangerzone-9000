#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"
/*! \brief An abstract class used to represent a bullet
 */
class Bullet : public GameObject
{
    private:
        int damage;
    public:
        /**
         * Constructor for Bullet
         * @param _positionX Bullet's initial X coordinate
         * @param _positionY Bullet's initial Y coordinate
         * @param _radius How many units wide the bullet is
         * @param _damage How much damage the bullet will inflict
         * @param _playerID Which player shot the bullet
         * @param _color What color the bullet is
         */
        Bullet(int _positionX, int _positionY, unsigned int _radius, unsigned int _damage,
               unsigned int _playerID, QBrush &_color);

        /**
         * States how much damage the bullet will inflict
         */
        int getDamage() {return damage;}

        /**
         * Moves the bullet and updates its X & Y coordinates
         * @return true if the bullet has moved out of bounds, false otherwise
         */
        virtual bool move()=0;
        virtual ~Bullet() {}
};

#endif // BULLET_H
