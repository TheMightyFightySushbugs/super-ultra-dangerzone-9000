#include "enemyship.h"

std::vector<Bullet*> EnemyShip::enemyBullets;

EnemyShip::EnemyShip(int _positionX, int _positionY, QBrush _color)
    : GameObject(_positionX, _positionY, _color)
{
}

int EnemyShip::shot(GameObject & target)
{
    int damage = 0;
    std::vector<Bullet*>::iterator previousBullet, currentBullet = enemyBullets.begin();
    while(currentBullet != enemyBullets.end())
    {
        if((*currentBullet)->collidesWith(target))
        {
            damage += (*currentBullet)->getDamage();
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

    return damage;
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
