#include "enemyship.h"

QBrush DummyShip::dummyColor = QBrush(QColor(155, 155, 155));

DummyShip::DummyShip(int _positionY)
    : EnemyShip(GAME_WIDTH + 7, _positionY, 1, 7, 6, 5, dummyColor)
{
}

bool DummyShip::move()
{
    positionX -= 2;
    if(positionX < -GAME_WIDTH - 7)
        return true;
    return false;
}

void DummyShip::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2,
                      flash ? Qt::white : dummyColor);
    flash=false;
}
