
#include "enemyship.h"

QBrush StraightShip::StraightShipColor = QBrush(QColor(155, 155, 155));

StraightShip::StraightShip(int _positionY)
    : EnemyShip(GAME_WIDTH + 15, _positionY, 6, 15, 10, 10, StraightShipColor)
{
}

bool StraightShip::move()
{
    positionX -= 2;
    if(positionX < -GAME_WIDTH - 15)
        return true;
    return false;
}

void StraightShip::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2,
                      flash ? Qt::white : StraightShipColor);
    flash=false;
}
