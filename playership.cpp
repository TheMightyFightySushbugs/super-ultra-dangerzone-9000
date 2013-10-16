#include "playership.h"
#include <QPainter>
#include <iostream>

extern QBrush peaGreen;

std::vector<Bullet*> PlayerShip::playerBullets;

PlayerShip::PlayerShip(int _positionX, int _positionY, QBrush _color)
    : GameObject(_positionX, _positionY, _color)
{
    health = 100;
    upPressed = downPressed = leftPressed = rightPressed = false;
    shootPressed = shootTapped = false;
}

void PlayerShip::draw(QPainter *painter)
{
    painter->setBrush(color);
    painter->drawRect(positionX-16, positionY-8, 32, 16);
}

void PlayerShip::interpretInput()
{
    //Horizontal movement
    if(leftPressed != rightPressed)
    {
        if(leftPressed)
            positionX -= 4;
        else
            positionX += 4;
    }
    //Vertical movement
    if(upPressed != downPressed)
    {
        if(upPressed)
            positionY -= 4;
        else
            positionY += 4;
    }

    if(shootTapped)
        playerBullets.push_back(new LinearBullet(positionX+16, positionY, 6, 0, 3, peaGreen));
    shootTapped = false;
}

bool PlayerShip::inflictDamage(int damage)
{
    //[to-do: add hit flashes]

    health -= damage;
    if(health <= 0)
        return true;
    return false;
}
int PlayerShip::shot(GameObject &target)
{
    int damage = 0;
    std::vector<Bullet*>::iterator previousBullet, currentBullet = playerBullets.begin();
    while(currentBullet != playerBullets.end())
    {
        if((*currentBullet)->collidesWith(target))
        {
            damage += (*currentBullet)->getDamage();
            delete *currentBullet;
            if(currentBullet == playerBullets.begin())
            {
                playerBullets.erase(currentBullet);
                currentBullet = playerBullets.begin();
                continue;
            }
            playerBullets.erase(currentBullet);
            currentBullet = previousBullet;
        }
        else
            previousBullet = currentBullet;
        currentBullet++;
    }

    return damage;
}

void PlayerShip::moveBullets()
{
    std::vector<Bullet*>::iterator previousBullet, currentBullet = playerBullets.begin();
    while(currentBullet != playerBullets.end())
    {
        if((*currentBullet)->move())
        {
            delete *currentBullet;
            if(currentBullet == playerBullets.begin())
            {
                playerBullets.erase(currentBullet);
                currentBullet = playerBullets.begin();
                continue;
            }
            playerBullets.erase(currentBullet);
            currentBullet = previousBullet;
        }
        else
            previousBullet = currentBullet;
        currentBullet++;
    }
}

void PlayerShip::drawBullets(QPainter * painter)
{
    std::vector<Bullet*>::iterator currentBullet = playerBullets.begin();
    while(currentBullet != playerBullets.end())
    {
        (*currentBullet)->draw(painter);
        currentBullet++;
    }
}
