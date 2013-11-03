#include "bullet.h"

Bullet::Bullet(int _positionX, int _positionY, unsigned int _radius, unsigned int _damage,
               unsigned int _playerID, QBrush &_color)
    : GameObject(_positionX, _positionY, _radius, _radius, _color)
{
    damage = _damage | (1 << (31-_playerID));
}
