#include "game.h"
#include "character.h"
#include "linesegment.h"

#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

#include <iostream>
using namespace std;

Game::Game()
{
    aspectRatio = 4.0/3;
    cameraX = cameraY = 0;
    granularity = 320;
    upPressed = downPressed = leftPressed = rightPressed = false;
    shootPressed = shootClicked = false;
    player.positionX = player.positionY = 0;

    background = QBrush(QColor(14, 32, 24));    //dull grey
    spaceship = QBrush(QColor(225, 128, 162));  //glorious pepto-bismol pink
}

void Game::gameLoop()
{
    //Horizontal movement
    if(leftPressed != rightPressed)
    {
        if(leftPressed)
            player.positionX -= 4;
        else
            player.positionX += 4;
    }
    //Vertical movement
    if(upPressed != downPressed)
    {
        if(upPressed)
            player.positionY -= 4;
        else
            player.positionY += 4;
    }

    if(shootClicked)
        player.shoot();
    shootClicked = false;
    //Keep ship within bounds
    //asdf
}

void Game::render(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(), background);
    int width = (int)(granularity*aspectRatio);
    painter->setWindow(cameraX - width/2, cameraY - granularity/2, width, granularity);

    painter->save();
    painter->setBrush(spaceship);

    //Draw player
    painter->drawRect(player.positionX-16, player.positionY-8, 32, 16);
    painter->restore();
}


void Game::handleKeyPressEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
            upPressed = true;
            break;
        case Qt::Key_Down:
            downPressed = true;
            break;
        case Qt::Key_Left:
            leftPressed = true;
            break;
        case Qt::Key_Right:
            rightPressed = true;
            break;
        case Qt::Key_Space:
            if(!shootPressed)
                shootClicked = true;
            shootPressed = true;
            break;
    }
}

void Game::handleKeyReleaseEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
            upPressed = false;
            break;
        case Qt::Key_Down:
            downPressed = false;
            break;
        case Qt::Key_Left:
            leftPressed = false;
            break;
        case Qt::Key_Right:
            rightPressed = false;
            break;
        case Qt::Key_Space:
            shootPressed = false;
            break;
    }
}

void Game::setAspectRatio(double newRatio)
{
    aspectRatio = newRatio;
}
