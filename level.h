#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "enemyship.h"
#include "gameevent.h"

class Level
{
    private:
        std::list<GameEvent*> eventList;

    public:
        Level();
        Level(std::string &file);
        void addEvent(int sec, int numEnemy, EnemyShip &enemy);
        void defineLength(int length);
        bool update(std::list<EnemyShip *> &enemies);
};

#endif // LEVEL_H
