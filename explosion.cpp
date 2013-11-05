#include "explosion.h"
#include <QPainter>

std::list<Explosion*> Explosion::explosions;

Explosion::Explosion(int _positionX, int _positionY, int _radius, int _time, QBrush &_color)
    : GameObject(_positionX, _positionY, _color)
{
    timeRemaining = _time;
    width = height = _radius;
}

void Explosion::draw(QPainter *painter)
{
    painter->fillRect(positionX-width, positionY-height, width*2, height*2, color);
}

void Explosion::drawAllExplosions(QPainter *painter)
{
    std::list<Explosion*>::iterator currentExplosion = explosions.begin();
    while(currentExplosion != explosions.end())
    {
        if(--((*currentExplosion)->timeRemaining) >= 0)
            (*currentExplosion++)->draw(painter);
        else
        {
            delete *currentExplosion;
            currentExplosion = explosions.erase(currentExplosion);
        }
    }
}

void Explosion::addExplosion(int _positionX, int _positionY, int _radius,
                             int _time, QBrush &_color)
{
    explosions.push_back(new Explosion(_positionX, _positionY, _radius, _time, _color));
}
