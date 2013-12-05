#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPainter>
#include <iostream> //Just in case I ever need to hack together some quick & dirty
                    //print-statement debugging

/*!
 * \brief An abstract class used as the basis for every object in the game
 */
class GameObject
{
    protected:
        int positionX, positionY;
        unsigned short width, height;
        QBrush color;
    public:
        /**
         * Draws this game object onto the screen
         * @param painter A QPainter object with which to paint
         */
        virtual void draw(QPainter *painter);

        /**
         * Determine whether this object is colliding with another object
         * @param target The object we're testing against
         * @return true if the objects are colliding, false otherwise
         */
        bool collidesWith(GameObject &target);

        /**
         * Constructor for GameObject
         * @param _positionX GameObject's initial X coordinate
         * @param _positionY GameObject's initial Y coordinate
         * @param _width How many units wide this GameObject is
         * @param _height How many units high this GameObject is
         * @param _color What color this GameObject is
         */
        GameObject(int _positionX, int _positionY, unsigned short _width,
                   unsigned short _height, const QBrush &_color);
};

const int GAME_WIDTH = 200;
const int GAME_HEIGHT = 150;

#endif // GAMEOBJECT_H
