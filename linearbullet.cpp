#include "linearbullet.h"
#include <QPainter>

LinearBullet::LinearBullet(int _positionX, int _positionY, int _velocityX, int _velocityY,
                           int _radius, unsigned int _playerID, QBrush &_color)
    : Bullet(_positionX, _positionY, 1, _playerID, _color)
{
    velocityX = _velocityX;
    velocityY = _velocityY;
    radius = _radius;
    width = height = _radius*2;
}

bool LinearBullet::move()
{
    positionX += velocityX;
    if(positionX < -160 - radius || positionX > 160 + radius)
        return true;
    positionY += velocityY;
    if(positionY < -120 - radius || positionY > 120 + radius)
        return true;
    return false;
}

QBrush peaGreen = QBrush(QColor(105, 200, 105));

void LinearBullet::draw(QPainter *painter)
{
    painter->fillRect(positionX-radius, positionY-radius, radius*2, radius*2, peaGreen);
}
