#include "enemyship.h"

QBrush DummyShip::dummyColor = QBrush(QColor(155, 155, 155));

DummyShip::DummyShip(int _positionY)
    : EnemyShip(180, _positionY, 3, 7, 6, 10, dummyColor)
{
}

bool DummyShip::move()
{
    positionX -= 2;
    if(positionX < -180 )
        return true;
    return false;
}

void DummyShip::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2,
                      flash ? Qt::white : dummyColor);
    flash=false;
}
