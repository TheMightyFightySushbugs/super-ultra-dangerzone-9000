#ifndef GAME_H
#define GAME_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include "playership.h"
#include "enemyship.h"
#include "level.h"

enum GameState {MAIN_MENU, STARTING_LEVEL, PLAYING_LEVEL, PAUSED, ENDING_LEVEL, GAME_OVER,
                HIGH_SCORE_DISPLAY};

class Game
{
    friend class SpawnerShip;

    public:
        Game();

    public:
        void gameLoop();
        void readHighscoreFile();
        void updateHighscores();
        void render(QPainter *painter);
        void displayHighscores(QPainter *painter);
        void handleKeyPressEvent(int key);
        void handleKeyReleaseEvent(int key);
        void handleMouseClick(int xPos, int yPos);
        void setAspectRatio(unsigned int width, unsigned int height);
        static void cleanUpEnemies();
        void cleanUpEverything();

    private:
        Level *currentLevel;
        GameState state;
        unsigned int windowHeight, windowWidth, windowXScale;
        PlayerShip player1, player2, player3, player4; //<-- I'll eventually make this into an array of ships;
        std::string *levelFileName;
        unsigned int countdownTimer, playerCount;
        unsigned int highscores[10];
        static std::list<EnemyShip*> enemies;
        QPixmap logo;
};

#endif // GAME_H
