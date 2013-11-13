#ifndef GAME_H
#define GAME_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include "playership.h"
#include "enemyship.h"
#include "level.h"

enum GameState {MAIN_MENU, STARTING_LEVEL, PLAYING_LEVEL, PAUSED, ENDING_LEVEL, GAME_OVER,
                HIGH_SCORE_DISPLAY, HIGH_SCORE_ENTER};

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
        void cleanUpEverything();

    private:
        QBrush background;
        Level *currentLevel;
        GameState state;
        int windowHeight, windowWidth;
        PlayerShip player1, player2, player3, player4; //<-- I'll eventually make this into an array of ships;
        std::list<EnemyShip*> enemies;
        std::string *levelFileName;
        unsigned int countdownTimer; //for animation & delays between levels
};

#endif // GAME_H
