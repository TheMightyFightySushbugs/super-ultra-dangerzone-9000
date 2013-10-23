#include "playership.h"
#include <QPainter>

extern QBrush peaGreen;

std::vector<Bullet*> PlayerShip::playerBullets;

PlayerShip::PlayerShip(int _positionX, int _positionY, QBrush _color)
    : GameObject(_positionX, _positionY, _color)
{
    health = lives = 1;
    visible = true;
    state = SPAWNING;
    spawnX = _positionX;
    positionY = spawnY = _positionY;
    positionX = spawnX - 81;
    upPressed = downPressed = leftPressed = rightPressed = false;
    shootPressed = shootTapped = false;
}

void PlayerShip::draw(QPainter *painter)
{
    if(visible)
        painter->fillRect(positionX-16, positionY-8, 32, 16, color);
}

void PlayerShip::interpretInput()
{
    if(state == SPAWNING)
    {
        if((positionX += 3) < spawnX)
        {
            visible = !visible;
            return;
        }
        visible = true;
        state = ALIVE;
    }

    //Horizontal movement
    if(leftPressed != rightPressed)
    {
        if(leftPressed)
        {
            if(positionX > -140)
                positionX -= 3;
        }
        else if(positionX < 140)
            positionX += 3;
    }
    //Vertical movement
    if(upPressed != downPressed)
    {
        if(upPressed)
        {
            if(positionY > -105)
                positionY -= 3;
        }
        else if(positionY < 105)
            positionY += 3;
    }

    if(shootTapped)
        playerBullets.push_back(new LinearBullet(positionX+16, positionY, 8, 0, 3, peaGreen));
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
    std::vector<Bullet*>::iterator currentBullet = playerBullets.begin();
    while(currentBullet != playerBullets.end())
    {
        if((*currentBullet)->collidesWith(target))
        {
            damage += (*currentBullet)->getDamage();
            delete *currentBullet;
            playerBullets.erase(currentBullet);
        }
        else
            currentBullet++;
    }

    return damage;
}

void PlayerShip::moveBullets()
{
    std::vector<Bullet*>::iterator currentBullet = playerBullets.begin();
    while(currentBullet != playerBullets.end())
    {
        if((*currentBullet)->move())
        {
            delete *currentBullet;
            playerBullets.erase(currentBullet);
        }
        else
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
