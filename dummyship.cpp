#include "enemyship.h"

QBrush DummyShip::dummyColor = QBrush(QColor(155, 155, 155));

DummyShip::DummyShip(int _positionX, int _positionY)
    : EnemyShip(_positionX, _positionY, 3, 10, dummyColor)
{
    width = 7; height = 6;
}

bool DummyShip::move()
{
    positionX -= 2;
    if(positionX < -180 || positionX > 180)
        return true;
    return false;
}

void DummyShip::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2, flash ? Qt::white : dummyColor);
    flash=false;
}
