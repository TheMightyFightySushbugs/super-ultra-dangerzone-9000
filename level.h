#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "enemyship.h"

class level
{
    private:
        std::list<GameEvent*> eventList;

    public:
        level();
        level(std::string &file);
        void addEvent(int sec, int numEnemy, EnemyShip &enemy);
        void defineLength(int length);
        void update();
};

#endif // LEVEL_H
