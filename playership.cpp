#include "playership.h"
#include <QPainter>
#include <iostream>

PlayerShip::PlayerShip(int _positionX, int _positionY, QBrush _color)
    : GameObject(_positionX, _positionY, _color)
{
    upPressed = downPressed = leftPressed = rightPressed = false;
    shootPressed = shootTapped = false;
}

void PlayerShip::draw(QPainter *painter)
{
    painter->setBrush(color);
    painter->drawRect(positionX-16, positionY-8, 32, 16);
}

void PlayerShip::interpretInput()
{
    //Horizontal movement
    if(leftPressed != rightPressed)
    {
        if(leftPressed)
            positionX -= 4;
        else
            positionX += 4;
    }
    //if either UP or DOWN (but not both) are pressed
    if(upPressed != downPressed)
    {
        if(upPressed)
            positionY -= 4;
        else
            positionY += 4;
    }

    if(shootTapped)
        std::cout << "pew!";
    std::cout << std::endl;
    shootTapped = false;
}
