#include "bullet.h"

Bullet::Bullet(int _positionX, int _positionY, int _damage, QBrush &_color)
    : GameObject(_positionX, _positionY, _color)
{
    damage = _damage;
}
