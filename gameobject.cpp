#include "gameobject.h"

GameObject::GameObject(int _positionX, int _positionY, unsigned short _width,
                       unsigned short _height, const QBrush &_color)
{
    positionX = _positionX;
    positionY = _positionY;
    width = _width;
    height = _height;
    color = _color;
}

bool GameObject::collidesWith(GameObject &target)
{
    if(target.positionX + target.width <= positionX - width)
        return false;
    if(target.positionX - target.width >= positionX + width)
        return false;
    if(target.positionY + target.height <= positionY - height)
        return false;
    if(target.positionY - target.height >= positionY + height)
        return false;
    return true;
}

void GameObject::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2, color);
}
