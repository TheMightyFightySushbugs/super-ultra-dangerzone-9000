#ifndef GAME_H
#define GAME_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include "playership.h"
#include "enemyship.h"
#include "level.h"

class Game
{
    public:
        Game();

    public:
        void gameLoop();
        void render(QPainter *painter, QPaintEvent *event);
        void handleKeyPressEvent(int key);
        void handleKeyReleaseEvent(int key);
        void setAspectRatio(double newAspectRatio);

    private:
        QBrush background;
        Level *currentLevel;// <-- not working
        int windowHeight, windowWidth;
        PlayerShip player1, player2, player3, player4; //<-- I'll eventually make this into an array of ships;
        std::list<EnemyShip*> enemies;
};

#endif // GAME_H
