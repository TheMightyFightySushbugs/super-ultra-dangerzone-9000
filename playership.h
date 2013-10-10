#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <vector>
#include "enemyship.h"
#include "linearbullet.h"

class PlayerShip : public GameObject
{
    private:
        static std::vector<Bullet*> playerBullets;
        bool upPressed, downPressed, leftPressed, rightPressed;
        bool shootPressed, shootTapped;
    public:
        PlayerShip(int _positionX, int _positionY, QBrush _color);
        void draw(QPainter *painter);
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
        static int shot(GameObject & target);
        static void moveBullets();
        static void drawBullets(QPainter *painter);
};

#endif // PLAYERSHIP_H
