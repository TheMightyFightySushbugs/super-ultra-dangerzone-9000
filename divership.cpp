#include "enemyship.h"

QBrush DiverShip::diverShipColor = QBrush(QColor(177, 18, 177));

DiverShip::DiverShip(int _positionY)
    : EnemyShip(GAME_WIDTH + 7, _positionY, 2, 7, 6, 5, diverShipColor)
{
}

bool DiverShip::move()
{
    positionX -= 4;
    positionY += 2;
    if(positionX < -GAME_WIDTH - 7)
        return true;
    return false;
}

void DiverShip::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2,
                      flash ? Qt::white : diverShipColor);
    flash=false;
}

