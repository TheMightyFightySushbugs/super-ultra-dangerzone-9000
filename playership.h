#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <list>
#include "enemyship.h"
#include "linearbullet.h"

enum PlayerShipState { SPAWNING, ALIVE, DEAD };

/*!
 * \brief A class used to represent a player's ship
 */
class PlayerShip : public GameObject
{
    private:
        int spawnX, spawnY;
        unsigned int health, lives, score, playerID, bombs;
        bool visible;
        PlayerShipState state;
        static std::list<Bullet*> playerBullets;
        bool upPressed, downPressed, leftPressed, rightPressed;
        bool shootPressed, shootTapped, bombPressed, bombTapped;
        static QBrush bombBlastColor;
    public:
        /**
         * Constructor for PlayerShip
         * @param _positionX PlayerShip's initial X position
         * @param _positionY PlayerShip's initial Y position
         * @param _playerID Which number player this is
         * @param _color What color this PlayerShip is
         */
        PlayerShip(int _positionX, int _positionY, unsigned int _playerID, QBrush _color);

        /**
         * Draw this PlayerShip on screen
         * @param painter A QPainter object with which to draw
         */
        void draw(QPainter *painter);

        /**
         * Draw this player's HUD on screen
         * @param painter A QPainter object with which to draw
         */
        void drawHUD(QPainter *painter);

        /**
         * Let this PlayerShip know that its corresponding Up button was pressed
         */
        void pressUp() {upPressed = true;}

        /**
         * Let this PlayerShip know that its corresponding Down button was pressed
         */
        void pressDown() {downPressed = true;}

        /**
         * Let this PlayerShip know that its corresponding Left button was pressed
         */
        void pressLeft() {leftPressed = true;}

        /**
         * Let this PlayerShip know that its corresponding Right button was pressed
         */
        void pressRight() {rightPressed = true;}

        /**
         * Let this PlayerShip know that its corresponding Shoot button was pressed
         */
        void pressShoot() {shootPressed = true;}

        /**
         * Let this PlayerShip know that its corresponding Bomb button was pressed
         */
        void pressBomb();

        /**
         * Let this PlayerShip know that its corresponding Up button was released
         */
        void releaseUp() {upPressed = false;}

        /**
         * Let this PlayerShip know that its corresponding Down button was released
         */
        void releaseDown() {downPressed = false;}

        /**
         * Let this PlayerShip know that its corresponding Left button was released
         */
        void releaseLeft() {leftPressed = false;}

        /**
         * Let this PlayerShip know that its corresponding Right button was released
         */
        void releaseRight() {rightPressed = false;}

        /**
         * Determine whether this PlayerShip is currently deploying a bomb
         * @return true if currently bombing, false otherwise
         */
        bool isBombing() {return bombPressed;}

        /**
         * Increment this player's score by '_increment'
         * @param _increment How many point to increment
         */
        void incrementScore(int _increment) {score += _increment;}
        unsigned int getScore() {return score;}

        /**
         * Interpret player's input and perform whatever actions must be performed for the
         * current frame.
         */
        void interpretInput();

        /**
         * Inflict "damage" amount of damage upon the ship
         * @param damage How much damage to inflict
         * @return true if damage was enough to destroy this ship, false otherwise
         */
        bool inflictDamage(unsigned int damage);

        /**
         * Creates an explosion at ship's current position, decrement 'lives' by 1, and resets
         * ship back to its starting position.
         */
        void kill();

        /**
         * Reset player ship back to its initial state (used when starting a new game)
         */
        void reset();

        PlayerShipState getState() {return state;}

        /**
         * Determine whether 'target' collides with any of the player's bullets
         * @param target The GameObject we're testing against
         * @return 0 if no bullets collided. Otherwise, it's the sum of all the damage the
         *         bullets inflict (along with the corresponding player ID bits to determine
         *         who was responsible)
         */
        static int shot(GameObject & target);

        /**
         * Move all player bullets & update their X & Y coordinates
         */
        static void moveBullets();

        /**
         * Draw all player bullets
         * @param painter A QPainter object with which to draw
         */
        static void drawBullets(QPainter *painter);

        /**
         * Clean up & delete all player bullets
         */
        static void cleanUpPlayerBullets();
};

#endif // PLAYERSHIP_H
