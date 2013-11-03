#include "enemyship.h"

std::list<Bullet*> EnemyShip::enemyBullets;

EnemyShip::EnemyShip(int _positionX, int _positionY, unsigned int _health,
                     int _width, int _height, unsigned int _pointValue, QBrush &_color)
    : GameObject(_positionX, _positionY, _width, _height, _color)
{
    health = _health;
    pointValue = _pointValue;
    flash=false;
}

unsigned int EnemyShip::inflictDamage(unsigned int _damage)
{
    unsigned int damageDecrement = _damage & 0x0FFFFFFF;
    if(health > damageDecrement)
    {
        health -= damageDecrement;
        flash=true;
        return 0;
    }

    QBrush expColor = QBrush(Qt::red); //This is a quick fix... I'll improve it later
    Explosion::addExplosion(positionX, positionY, width, 15, expColor);

    return pointValue | (_damage & 0xF0000000);
}

unsigned int EnemyShip::shot(GameObject & target)
{
    unsigned int _damage = 0;
    std::list<Bullet*>::iterator currentBullet = enemyBullets.begin();
    while(currentBullet != enemyBullets.end())
    {
        if((*currentBullet)->collidesWith(target))
        {
            unsigned int damageIncrement = (*currentBullet)->getDamage();
            delete *currentBullet;
            currentBullet = enemyBullets.erase(currentBullet);
            _damage = (_damage | (damageIncrement & 0xF0000000))
                    + (damageIncrement & 0x0FFFFFFF);
        }
        else
            currentBullet++;
    }

    return _damage;
}

void EnemyShip::moveBullets()
{
    std::list<Bullet*>::iterator currentBullet = enemyBullets.begin();
    while(currentBullet != enemyBullets.end())
    {
        if((*currentBullet)->move())
        {
            delete *currentBullet;
            currentBullet = enemyBullets.erase(currentBullet);
        }
        else
            currentBullet++;
    }
}

void EnemyShip::drawBullets(QPainter *painter)
{
    std::list<Bullet*>::iterator currentBullet = enemyBullets.begin();
    while(currentBullet != enemyBullets.end())
    {
        (*currentBullet)->draw(painter);
        currentBullet++;
    }
}
