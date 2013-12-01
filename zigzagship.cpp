#include "enemyship.h"
#include "linearbullet.h"

QBrush ZigZagShip::zigZagColor = QBrush(QColor(0, 255, 0));

ZigZagShip::ZigZagShip(int _positionY)
    : EnemyShip(GAME_WIDTH + 7, _positionY, 2, 7, 6, 10, zigZagColor)
{
    timer = 45;
    movingUp = false;
}

bool ZigZagShip::move()
{
    positionX--;
    if(positionX < -GAME_WIDTH - 7)
        return true;

    if(movingUp)
        positionY--;
    else
        positionY++;

    if(--timer < 0)
    {
        enemyBullets.push_back(new LinearBullet(positionX-6, positionY, -2, 0, 0, zigZagColor));
        timer = 45;
        movingUp = !movingUp;
    }
    return false;
}

void ZigZagShip::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2,
                      flash ? Qt::white : zigZagColor);
    flash=false;
}
