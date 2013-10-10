#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QBrush>

class GameObject
{
    protected:
        int positionX, positionY;
        QBrush color;
    public:
        virtual void draw(QPainter *painter)=0;
        GameObject(int _positionX, int _positionY, QBrush _color);
};

#endif // GAMEOBJECT_H
