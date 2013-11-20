#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <list>
#include "enemyship.h"
#include "linearbullet.h"
#include "bomb.h"

enum PlayerShipState { SPAWNING, ALIVE, DEAD };

class PlayerShip : public GameObject
{
    private:
        int spawnX, spawnY;
        unsigned int health, lives, score, playerID, bombs;
        bool visible;
        PlayerShipState state;
        static std::list<Bullet*> playerBullets;
        bool upPressed, downPressed, leftPressed, rightPressed;
        bool shootPressed, shootTapped;
        bool bombPressed, bombTapped;
    public:
        PlayerShip(int _positionX, int _positionY, unsigned int _playerID, QBrush _color);
        void draw(QPainter *painter);
        void drawHUD(QPainter *painter);
        void drawLives(QPainter *painter);
        void pressUp() {upPressed = true;}
        void pressDown() {downPressed = true;}
        void pressLeft() {leftPressed = true;}
        void pressRight() {rightPressed = true;}
        void pressShoot() {if(!shootPressed) shootTapped = true; shootPressed = true;}
        void pressBomb() {if (!bombPressed) bombTapped = true; bombPressed = true;}
        void releaseUp() {upPressed = false;}
        void releaseDown() {downPressed = false;}
        void releaseLeft() {leftPressed = false;}
        void releaseRight() {rightPressed = false;}
        void releaseShoot() {shootPressed = false;}
        void releaseBomb() {bombPressed = false;}
        void incrementScore(int _increment) {score += _increment;}
        unsigned int getScore() {return score;}

        //Interpret player's input and perform whatever actions must be performed for the
        //current frame.
        void interpretInput();

        //Inflicts "damage" amount of damage upon the ship and returns true if that was enough
        //to destroy it.
        bool inflictDamage(unsigned int damage);

        //Creates an explosion at ship's current position, decrement 'lives' by 1, and resets
        //ship back to its starting position.
        void kill();

        PlayerShipState getState() {return state;}
        static int shot(GameObject & target);
        static void moveBullets();
        static void drawBullets(QPainter *painter);
        static void cleanUpPlayerBullets();
};

#endif // PLAYERSHIP_H
