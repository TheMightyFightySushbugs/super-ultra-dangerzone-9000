#include "enemyship.h"
#include "linearbullet.h"
#include "game.h"

QBrush SpawnerShip::spawnerColor = QBrush(QColor(0, 128, 128));

SpawnerShip::SpawnerShip(int _positionY)
    : EnemyShip(GAME_WIDTH + 15, _positionY, 36, 15, 20, 1000, spawnerColor)
{
    timerX = 119;
    timerY = 26;
    movingUp = false;
    movingLeft = true;
    velocityY = 0;
    velocityX = -1;
}

bool SpawnerShip::move()
{
    if(positionX <= GAME_WIDTH)
    {
        if(movingLeft)
            velocityX -= (timerX % 4 == 1 && velocityX > -3) ? 1 : 0;
        else
            velocityX += (timerX % 4 == 1 && velocityX < 3) ? 1 : 0;

        if(--timerX < 0)
        {
            timerX = 119;
            movingLeft = !movingLeft;
        }
    }

    if(movingUp)
        velocityY -= (velocityY > -5) ? 1 : 0;
    else
        velocityY += (velocityY < 5) ? 1 : 0;

    positionX += velocityX;
    positionY += velocityY;

    if(timerY % 15 == 1)
        enemyBullets.push_back(new LinearBullet(positionX-15, positionY, -3, 0, 0, spawnerColor));
    if(timerY % 36 == 1)
        Game::enemies.push_back(new DummyShip(positionY));

    if(--timerY < 0)
    {
        timerY = 57;
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

unsigned int SpawnerShip::inflictDamage(unsigned int _damage)
{
    unsigned int pointValue = EnemyShip::inflictDamage(_damage);
    if(pointValue != 0)
    {
        Game::cleanUpEnemies();
        QBrush red = QBrush(Qt::red);
        Explosion::addExplosion(0, 0, GAME_WIDTH, 2, red);
    }
    return pointValue;
}
