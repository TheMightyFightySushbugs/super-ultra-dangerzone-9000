#include "enemyship.h"

std::list<Bullet*> EnemyShip::enemyBullets;

EnemyShip::EnemyShip(int _positionX, int _positionY, int _health, QBrush &_color)
    : GameObject(_positionX, _positionY, _color)
{
    health = _health;
}

bool EnemyShip::inflictDamage(int _damage)
{
    //[to-do: add hit flashes]

    if((health -= _damage) > 0)
        return false;

    QBrush expColor = QBrush(Qt::red); //This is a quick fix... I'll improve it later
    Explosion::addExplosion(positionX, positionY, width, 15, expColor);
    return true;
}

int EnemyShip::shot(GameObject & target)
{
    int _damage = 0;
    std::list<Bullet*>::iterator currentBullet = enemyBullets.begin();
    while(currentBullet != enemyBullets.end())
    {
        if((*currentBullet)->collidesWith(target))
        {
            _damage += (*currentBullet)->getDamage();
            delete *currentBullet;
            currentBullet = enemyBullets.erase(currentBullet);
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
