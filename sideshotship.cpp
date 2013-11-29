#include "enemyship.h"
#include "linearbullet.h"

QBrush SideShotShip::sideShotColor = QBrush(QColor(220, 220, 0));

SideShotShip::SideShotShip(int _positionY)
    : EnemyShip(GAME_WIDTH + 7, _positionY, 2, 7, 6, 21, sideShotColor)
{
    shooting = false;
    timer = 50;
}

bool SideShotShip::move()
{
    if(!shooting)
    {
        positionX -= 2;
        if(positionX < -GAME_WIDTH - 7)
            return true;
    }
    else if(timer % 10 == 5)
    {
        enemyBullets.push_back(new LinearBullet(positionX, positionY-6, 0,-2, 0, sideShotColor));
        enemyBullets.push_back(new LinearBullet(positionX, positionY-6, 0, 2, 0, sideShotColor));
    }

    if(--timer == 0)
    {
        shooting = !shooting;
        timer = (shooting) ? 10 : 50;
    }
    return false;
}

void SideShotShip::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2,
                      flash ? Qt::white : sideShotColor);
    flash=false;
}
