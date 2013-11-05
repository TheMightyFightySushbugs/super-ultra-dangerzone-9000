#ifndef LINEARBULLET_H
#define LINEARBULLET_H

#include "bullet.h"

class LinearBullet : public Bullet
{
    private:
        int velocityX, velocityY, radius;
    public:
        LinearBullet(int _positionX, int _positionY, int _velocityX, int _velocityY,
                     int _radius, unsigned int _playerID, QBrush &_color);
        bool move();
        void draw(QPainter *painter);
        ~LinearBullet() {};
};

#endif // LINEARBULLET_H
