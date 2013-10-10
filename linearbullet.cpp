#include "linearbullet.h"
#include <QPainter>

LinearBullet::LinearBullet(int _positionX, int _positionY, int _velocityX, int _velocityY,
                           int _radius, QBrush _color)
    : Bullet(_positionX, _positionY, _color)
{
    velocityX = _velocityX;
    velocityY = _velocityY;
    radius = _radius;
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

QBrush peaGreen = QBrush(QColor(155, 255, 155));

void LinearBullet::draw(QPainter *painter)
{
    painter->setBrush(peaGreen);
    painter->drawRect(positionX-radius, positionY-radius, radius*2, radius*2);
}
