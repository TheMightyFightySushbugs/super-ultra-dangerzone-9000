#ifndef LINEARBULLET_H
#define LINEARBULLET_H

#include "bullet.h"

class LinearBullet : public Bullet
{
    private:
        int velocityX, velocityY;
    public:
        LinearBullet(int _positionX, int _positionY, int _velocityX, int _velocityY,
                     unsigned int _playerID, QBrush &_color);
        bool move();
        ~LinearBullet() {}
};

#endif // LINEARBULLET_H
