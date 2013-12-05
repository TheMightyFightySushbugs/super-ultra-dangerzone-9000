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

/*!
 * \brief The class that holds the entire state of the game and handles everything
 */
class Game
{
    friend class SpawnerShip;

    public:
        Game();

    public:
        /**
         * Do everything that needs to be done in the current frame
         */
        void gameLoop();

        /**
         * Populate highscores array with the scores in highscore.txt
         */
        void readHighscoreFile();

        /**
         * Determine if there are any new highscores and store them into highscores.txt
         */
        void updateHighscores();

        /**
         * Draw what's currently happening in the game
         * @param painter A QPainter object with which to draw
         */
        void render(QPainter *painter);

        /**
         * Display the list of high scores on screen
         * @param painter A QPainter object with which to draw
         */
        void displayHighscores(QPainter *painter);

        /**
         * Handle and interpret a key press
         * @param key Which key was pressed
         */
        void handleKeyPressEvent(int key);

        /**
         * Handle and interpret a key release
         * @param key Which key was released
         */
        void handleKeyReleaseEvent(int key);

        /**
         * Handle and interpret a mouse click
         * @param key Which mouse button was clicked
         */
        void handleMouseClick(int xPos, int yPos);

        /**
         * Rescale rendering context as necessary if window is resized
         * @param width New window width
         * @param height New window height
         */
        void setAspectRatio(unsigned int width, unsigned int height);

        /**
         * Clean up and delete all enemies
         */
        static void cleanUpEnemies();

        /**
         * Clean up and delete anything Game may have allocated over time
         */
        void cleanUpEverything();

    private:
        Level *currentLevel;
        GameState state;
        unsigned int windowHeight, windowWidth, windowXScale;
        PlayerShip player1, player2, player3, player4; //<-- I'll eventually make this into an array of ships;
        std::string *levelFileName;
        unsigned int countdownTimer, playerCount, levelCount;
        unsigned int highscores[10];
        static std::list<EnemyShip*> enemies;
        QPixmap logo, game_over, paused;
};

#endif // GAME_H
