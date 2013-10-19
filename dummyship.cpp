#include "enemyship.h"

QBrush DummyShip::dummyColor = QBrush(QColor(155, 155, 155));

DummyShip::DummyShip(int _positionX, int _positionY)
    : EnemyShip(_positionX, _positionY, 1, dummyColor)
{
    width = 10; height = 6;
}

bool DummyShip::move()
{
    positionX -= 1;
    if(positionX < -180 || positionX > 180)
        return true;
    return false;
}

void DummyShip::draw(QPainter *painter)
{
    painter->setBrush(dummyColor);
    painter->drawRect(positionX-width, positionY-height, width*2, height*2);
}
