#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <list>
#include "enemyship.h"
#include "linearbullet.h"

enum PlayerShipState { SPAWNING, ALIVE, DEAD };

class PlayerShip : public GameObject
{
    private:
        int health, spawnX, spawnY;
        unsigned int lives, score, playerID;
        bool visible;
        PlayerShipState state;
        static std::list<Bullet*> playerBullets;
        bool upPressed, downPressed, leftPressed, rightPressed;
        bool shootPressed, shootTapped;
    public:
        PlayerShip(int _positionX, int _positionY, unsigned int _playerID, QBrush _color);
        void draw(QPainter *painter);
        void drawHUD(QPainter *painter);
        void pressUp() {upPressed = true;}
        void pressDown() {downPressed = true;}
        void pressLeft() {leftPressed = true;}
        void pressRight() {rightPressed = true;}
        void pressShoot() {if(!shootPressed) shootTapped = true; shootPressed = true;}
        void releaseUp() {upPressed = false;}
        void releaseDown() {downPressed = false;}
        void releaseLeft() {leftPressed = false;}
        void releaseRight() {rightPressed = false;}
        void releaseShoot() {shootPressed = false;}
        void incrementScore(int _increment) {score += _increment;}
        void interpretInput();
        bool inflictDamage(int damage);
        void kill(); // <-- Not yet implemented... Will create an explosion at ship's current
                     // position, decrement 'lives' by 1, and reset ship back to its starting
                     // position.
        int howMuchLivesLeft() {return lives;}
        PlayerShipState getState() {return state;}
        static int shot(GameObject & target);
        static void moveBullets();
        static void drawBullets(QPainter *painter);
};

#endif // PLAYERSHIP_H
