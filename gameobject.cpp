#include "gameobject.h"

GameObject::GameObject(int _positionX, int _positionY, QBrush _color)
{
    positionX = _positionX;
    positionY = _positionY;
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
