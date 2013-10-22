#include "explosion.h"
#include <QPainter>

Explosion::Explosion(int _positionX, int _positionY, int _radius, QBrush &_color)
    : GameObject(_positionX, _positionY, _color)
{
    width = height = _radius;
}

void Explosion::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2, color);
}
