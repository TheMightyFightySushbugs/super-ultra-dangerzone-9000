#ifndef LINEARBULLET_H
#define LINEARBULLET_H

#include "bullet.h"

/*!
 * \brief A bullet that moves in a straight line at a constant velocity
 */
class LinearBullet : public Bullet
{
    private:
        int velocityX, velocityY;
    public:
        /**
         * Constructor for LinearBullet
         * @param _positionX LinearBullet's initial X coordinate
         * @param _positionY LinearBullet's initial Y coordinate
         * @param _velocityX LinearBullet's velocity along the X-axis
         * @param _velocityY LinearBullet's velocity along the Y-axis
         * @param _playerID Which player shot this LinearBullet
         * @param _color What color this LinearBullet is
         */
        LinearBullet(int _positionX, int _positionY, int _velocityX, int _velocityY,
                     unsigned int _playerID, QBrush &_color);

        /**
         * Moves the bullet and updates its X & Y coordinates
         * @return true if the bullet has moved out of bounds, false otherwise
         */
        bool move();
        ~LinearBullet() {}
};

#endif // LINEARBULLET_H
