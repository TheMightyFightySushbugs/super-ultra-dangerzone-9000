#include "playership.h"
#include "explosion.h"
#include <QPainter>
#include <stdio.h>

extern QBrush peaGreen;

std::list<Bullet*> PlayerShip::playerBullets;

PlayerShip::PlayerShip(int _positionX, int _positionY, unsigned int _playerID, QBrush _color)
    : GameObject(_positionX, _positionY, 16, 8, _color)
{
    playerID = _playerID;
    spawnX = _positionX;
    positionY = spawnY = _positionY;
}

void PlayerShip::reset()
{
    score = 0;
    health = 1;
    lives = 3;
    bombs = 3;
    visible = true;
    state = SPAWNING;
    positionX = spawnX - 81;
    upPressed = downPressed = leftPressed = rightPressed = false;
    shootPressed = bombPressed = false;
}

void PlayerShip::draw(QPainter *painter)
{
    if(visible)
        painter->fillRect(positionX-16, positionY-8, 32, 16, color);
    bombPressed = false;
}

void PlayerShip::drawHUD(QPainter *painter)
{
    char score_str[9];
    sprintf(score_str, "%08i", score);
    char lives_str[6];
    sprintf(lives_str, "x%i", lives);
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 9));
    painter->drawText(10 - GAME_WIDTH + (GAME_WIDTH/2)*playerID, -GAME_HEIGHT + 10, score_str);
    painter->setFont(QFont("Arial", 7));
    painter->drawText(20 - GAME_WIDTH + (GAME_WIDTH/2)*playerID, 18 - GAME_HEIGHT, lives_str);
    painter->fillRect(10 - GAME_WIDTH + (GAME_WIDTH/2)*playerID, 11 - GAME_HEIGHT, 9, 7, color);
    for(unsigned int i = 0; i < bombs; i++)
        painter->fillRect(35 - GAME_WIDTH + (GAME_WIDTH/2)*playerID + 10*i, 11-GAME_HEIGHT, 7,
                          7, color);
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
            if(positionX > -GAME_WIDTH + 20)
                positionX -= 3;
        }
        else if(positionX < GAME_WIDTH - 20)
            positionX += 3;
    }
    //Vertical movement
    if(upPressed != downPressed)
    {
        if(upPressed)
        {
            if(positionY > -GAME_HEIGHT + 30)
                positionY -= 3;
        }
        else if(positionY < GAME_HEIGHT - 15)
            positionY += 3;
    }

    if(shootPressed)
        playerBullets.push_back(new LinearBullet(positionX + 16, positionY, 8, 0,
                                                 playerID, peaGreen));
    shootPressed = false;
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
    bombs = 3;
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

void PlayerShip::cleanUpPlayerBullets()
{
    std::list<Bullet*>::iterator currentBullet = playerBullets.begin();
    while(currentBullet != playerBullets.end())
        delete *currentBullet++;
    playerBullets.clear();
}

QBrush PlayerShip::bombBlastColor = QBrush(Qt::white);

void PlayerShip::pressBomb()
{
    if(state != ALIVE || bombs == 0)
        return;
    bombs--;
    bombPressed = true;
    Explosion::addExplosion(0, 0, GAME_WIDTH, 3, bombBlastColor);
}
