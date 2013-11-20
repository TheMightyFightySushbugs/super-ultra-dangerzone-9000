#ifndef BOMB_H
#define BOMB_H

#include "bullet.h"

class Bomb : public Bullet
{
private:
    int counter;
public :
    Bomb(unsigned int _playerID);
    bool move();
    ~Bomb() {}
};

#endif // BOMB_H
