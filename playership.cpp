#include "playership.h"
#include <QPainter>
#include <stdio.h>

extern QBrush peaGreen;

std::list<Bullet*> PlayerShip::playerBullets;

PlayerShip::PlayerShip(int _positionX, int _positionY, unsigned int _playerID, QBrush _color)
    : GameObject(_positionX, _positionY, _color)
{
    playerID = _playerID;
    score = 0;
    health = 1;
    lives = 3;
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

void PlayerShip::drawHUD(QPainter *painter)
{
    char score_str[32];
    sprintf(score_str, "%i", score);
    char lives_str[10];
    sprintf(lives_str, "P%i x %i", playerID + 1, lives);
    painter->drawText(-145 + 80*playerID, -105, score_str);
    painter->fillRect(-155 + 80*playerID, -100, 14, 9, color);
    painter->drawText(-135 + 80*playerID, -90, lives_str);
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
        playerBullets.push_back(new LinearBullet(positionX + 16, positionY, 8, 0, 3,
                                                 playerID, peaGreen));
    shootTapped = false;
}

bool PlayerShip::inflictDamage(unsigned int damage)
{
    if(damage >= health)
    {
        kill();
        return true;
    }

    health -= damage;
    return false;
}

void PlayerShip::kill()
{
    QBrush expColor = QBrush(Qt::red); //This is a quick fix... I'll improve it later
    Explosion::addExplosion(positionX, positionY, 17, 15, expColor);

    health = 1;
    if(--lives == 0)
    {
        state = DEAD;
        visible = false;
    }
    else
    {
        state = SPAWNING;
        positionY = spawnY;
        positionX = spawnX - 81;
    }
}

int PlayerShip::shot(GameObject &target)
{
    int damage = 0;
    std::list<Bullet*>::iterator currentBullet = playerBullets.begin();
    while(currentBullet != playerBullets.end())
    {
        if((*currentBullet)->collidesWith(target))
        {
            damage += (*currentBullet)->getDamage();
            delete *currentBullet;
            currentBullet = playerBullets.erase(currentBullet);
        }
        else
            currentBullet++;
    }

    return damage;
}

void PlayerShip::moveBullets()
{
    std::list<Bullet*>::iterator currentBullet = playerBullets.begin();
    while(currentBullet != playerBullets.end())
    {
        if((*currentBullet)->move())
        {
            delete *currentBullet;
            currentBullet = playerBullets.erase(currentBullet);
        }
        else
            currentBullet++;
    }
}

void PlayerShip::drawBullets(QPainter * painter)
{
    std::list<Bullet*>::iterator currentBullet = playerBullets.begin();
    while(currentBullet != playerBullets.end())
    {
        (*currentBullet)->draw(painter);
        currentBullet++;
    }
}
