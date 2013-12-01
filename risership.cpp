#include "enemyship.h"

QBrush RiserShip::riserShipColor = QBrush(QColor(177, 18, 177));

RiserShip::RiserShip(int _positionY)
    : EnemyShip(GAME_WIDTH + 7, _positionY, 2, 7, 6, 5, riserShipColor)
{
}

bool RiserShip::move()
{
    positionX -= 4;
    positionY += 2;
    if(positionX < -GAME_WIDTH - 7)
        return true;
    return false;
}

void RiserShip::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2,
                      flash ? Qt::white : riserShipColor);
    flash=false;
}
