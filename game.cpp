#include "game.h"
#include "playership.h"

#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

#include <iostream>

Game::Game() : player1(0, 0, QBrush(QColor(225, 128, 162)))
{
    aspectRatio = 4.0/3;
    cameraX = cameraY = 0;
    granularity = 320;
    background = QBrush(QColor(14, 32, 24));
}

void Game::gameLoop()
{
    //Let player 1 do whatever it has to do (move/shoot/etc)
    player1.interpretInput();
    PlayerShip::moveBullets();

    //For every enemy ship...
    unsigned int damage;
    std::vector<EnemyShip*>::iterator previousEnemy, currentEnemy = enemies.begin();
    while(currentEnemy != enemies.end())
    {
        //Let the ship do whatever it has to do (move/shoot/etc)
        (*currentEnemy)->move();

        //[to-do: check when enemies go out of bounds. delete them when they do]

        //Check to see if any of the player's bullets hit the ship
        damage = PlayerShip::shot(**currentEnemy);

        //If any bullets did hit, and they inflicted enough damage to destroy the ship...
        if(damage && (*currentEnemy)->inflictDamage(damage))
        {
            //[to-do: add explosion. Right now the enemy just disappears, which isn't very
            //satisfying for the player]

            //...then go ahead and destroy the ship
            delete *currentEnemy;
            if(currentEnemy == enemies.begin())
            {
                enemies.erase(currentEnemy);
                currentEnemy = enemies.begin();
                continue;
            }
            enemies.erase(currentEnemy);
            currentEnemy = previousEnemy;
        }
        else
            previousEnemy = currentEnemy;
        currentEnemy++;

        //Check to see if any enemy bullets hit player 1
        damage = EnemyShip::shot(player1);

        //If any bullets did hit, and they inflicted enough damage to destroy the ship...
        if(damage && player1.inflictDamage(damage))
        {
            //[to-do: set up lives/respawning/etc]
            std::cout << "Player 1 died!\n";
        }
    }
}

void Game::render(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(), background);
    int width = (int)(granularity*aspectRatio);
    painter->setWindow(cameraX - width/2, cameraY - granularity/2, width, granularity);
    painter->save();
    player1.draw(painter);
    PlayerShip::drawBullets(painter);
    painter->restore();
}

void Game::handleKeyPressEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
            player1.pressUp();
            break;
        case Qt::Key_Down:
            player1.pressDown();
            break;
        case Qt::Key_Left:
            player1.pressLeft();
            break;
        case Qt::Key_Right:
            player1.pressRight();
            break;
        case Qt::Key_Space:
            player1.pressShoot();
            break;
    }
}

void Game::handleKeyReleaseEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
            player1.releaseUp();
            break;
        case Qt::Key_Down:
            player1.releaseDown();
            break;
        case Qt::Key_Left:
            player1.releaseLeft();
            break;
        case Qt::Key_Right:
            player1.releaseRight();
            break;
        case Qt::Key_Space:
            player1.releaseShoot();
            break;
    }
}

void Game::setAspectRatio(double newRatio)
{
    aspectRatio = newRatio;
}
