#include "bomb.h"
#include "explosion.h"
#include <QPainter>

Bomb::Bomb(unsigned int _playerID)
    : Bullet (0, 0,GAME_WIDTH*2,50,_playerID, QBrush(Qt::white ))
{
   counter = 20;
   Explosion::addExplosion(0, 0, GAME_WIDTH*2, 20, QBrush(Qt::white));
}


bool Bomb::move()
{
    return(--counter ==0);
}
