#include "linearbullet.h"
#include <QPainter>

LinearBullet::LinearBullet(int _positionX, int _positionY, int _velocityX, int _velocityY,
                           unsigned int _playerID, QBrush &_color)
    : Bullet(_positionX, _positionY, 3, 1, _playerID, _color)
{
    velocityX = _velocityX;
    velocityY = _velocityY;
}

bool LinearBullet::move()
{
    positionX += velocityX;
    if(positionX < -160 - width || positionX > 160 + width)
        return true;
    positionY += velocityY;
    if(positionY < -120 - height || positionY > 120 + height)
        return true;
    return false;
}

QBrush peaGreen = QBrush(QColor(105, 200, 105));
