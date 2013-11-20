#include "enemyship.h"
#include "linearbullet.h"
#include "game.h"

QBrush SpawnerShip::spawnerColor = QBrush(QColor(0, 128, 128));

SpawnerShip::SpawnerShip(int _positionY)
    : EnemyShip(GAME_WIDTH + 15, _positionY, 50, 15, 20, 1000, spawnerColor)
{
    timer = 27;
    movingUp = false;
    velocityY = 0;
}

bool SpawnerShip::move()
{
    if(positionX > (GAME_WIDTH * 3) / 4)
        positionX--;

    if(movingUp)
        velocityY -= (velocityY > -5) ? 1 : 0;
    else
        velocityY += (velocityY < 5) ? 1 : 0;
    positionY += velocityY;

    if(timer % 15 == 0)
        enemyBullets.push_back(new LinearBullet(positionX-15, positionY, -3, 0, 0, spawnerColor));
    if(timer % 25 == 0)
        Game::enemies.push_back(new ZigZagShip(positionY));

    if(--timer < 0)
    {
        timer = 57;
        movingUp = !movingUp;
    }

    return false;
}

void SpawnerShip::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2,
                      flash ? Qt::white : spawnerColor);
    flash = false;
}
