#include "enemyship.h"

std::vector<Bullet*> EnemyShip::enemyBullets;

EnemyShip::EnemyShip(int _positionX, int _positionY, int _health, QBrush &_color)
    : GameObject(_positionX, _positionY, _color)
{
    health = _health;
}

bool EnemyShip::inflictDamage(int _damage)
{
    //[to-do: add hit flashes]

    health -= _damage;
    if(health <= 0)
        return true;
    return false;
}

int EnemyShip::shot(GameObject & target)
{
    int _damage = 0;
    std::vector<Bullet*>::iterator previousBullet, currentBullet = enemyBullets.begin();
    while(currentBullet != enemyBullets.end())
    {
        if((*currentBullet)->collidesWith(target))
        {
            _damage += (*currentBullet)->getDamage();
            delete *currentBullet;
            if(currentBullet == enemyBullets.begin())
            {
                enemyBullets.erase(currentBullet);
                currentBullet = enemyBullets.begin();
                continue;
            }
            enemyBullets.erase(currentBullet);
            currentBullet = previousBullet;
        }
        else
            previousBullet = currentBullet;
        currentBullet++;
    }

    return _damage;
}

void EnemyShip::moveBullets()
{
    std::vector<Bullet*>::iterator previousBullet, currentBullet = enemyBullets.begin();
    while(currentBullet != enemyBullets.end())
    {
        if((*currentBullet)->move())
        {
            delete *currentBullet;
            if(currentBullet == enemyBullets.begin())
            {
                enemyBullets.erase(currentBullet);
                currentBullet = enemyBullets.begin();
                continue;
            }
            enemyBullets.erase(currentBullet);
            currentBullet = previousBullet;
        }
        else
            previousBullet = currentBullet;
        currentBullet++;
    }
}

void EnemyShip::drawBullets(QPainter *painter)
{
    std::vector<Bullet*>::iterator currentBullet = enemyBullets.begin();
    while(currentBullet != enemyBullets.end())
    {
        (*currentBullet)->draw(painter);
        currentBullet++;
    }
}
