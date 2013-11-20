#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPainter>
#include <iostream> //Just in case I ever need to hack together some quick & dirty
                    //print-statement debugging

class GameObject
{
    protected:
        int positionX, positionY;
        unsigned short width, height;
        QBrush color;
    public:
        virtual void draw(QPainter *painter);
        bool collidesWith(GameObject &target);
        GameObject(int _positionX, int _positionY, unsigned short _width,
                   unsigned short _height, const QBrush &_color);
};

const int GAME_WIDTH = 200;
const int GAME_HEIGHT = 150;

#endif // GAMEOBJECT_H
