#ifndef GAME_H
#define GAME_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <playership.h>
#include <enemyship.h>

class Game
{
    public:
        Game();

    public:
        void gameLoop();
        void render(QPainter *painter, QPaintEvent *event);
        void handleKeyPressEvent(int key);
        void handleKeyReleaseEvent(int key);
        void setAspectRatio(double newRatio);

    private:
        QBrush background;
        int cameraX, cameraY;
        int granularity;
        double aspectRatio;
        PlayerShip player1; //<-- I'll eventually make this into an array of ships;
        std::vector<EnemyShip*> enemies;
};

#endif // GAME_H
