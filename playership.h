#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <list>
#include "enemyship.h"
#include "linearbullet.h"

enum PlayerShipState { SPAWNING, ALIVE, DEAD };

class PlayerShip : public GameObject
{
    private:
        int health, lives, score, spawnX, spawnY;
        bool visible;
        PlayerShipState state;
        static std::list<Bullet*> playerBullets;
        bool upPressed, downPressed, leftPressed, rightPressed;
        bool shootPressed, shootTapped;
    public:
        PlayerShip(int _positionX, int _positionY, QBrush _color);
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
        void interpretInput();
        bool inflictDamage(int damage);
        void kill();
        int howMuchLivesLeft();
        PlayerShipState getState() {return state;}
        static int shot(GameObject & target);
        static void moveBullets();
        static void drawBullets(QPainter *painter);
};

#endif // PLAYERSHIP_H
