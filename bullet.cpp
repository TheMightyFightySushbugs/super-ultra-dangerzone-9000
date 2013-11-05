#include "bullet.h"

Bullet::Bullet(int _positionX, int _positionY, int _damage, unsigned int _playerID,
               QBrush &_color)
    : GameObject(_positionX, _positionY, _color)
{
    damage = _damage | (1 << (31-_playerID));
}
