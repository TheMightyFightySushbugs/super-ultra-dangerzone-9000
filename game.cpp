#include "game.h"
#include "playership.h"

#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

#include <iostream>
using namespace std;

Game::Game() : player1(0, 0, QBrush(QColor(225, 128, 162)))
{
    aspectRatio = 4.0/3;
    cameraX = cameraY = 0;
    granularity = 320;
    background = QBrush(QColor(14, 32, 24));
}

void Game::gameLoop()
{
    player1.interpretInput();
}

void Game::render(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(), background);
    int width = (int)(granularity*aspectRatio);
    painter->setWindow(cameraX - width/2, cameraY - granularity/2, width, granularity);
    painter->save();
    player1.draw(painter);
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
