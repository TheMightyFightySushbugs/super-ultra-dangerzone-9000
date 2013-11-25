#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "enemyship.h"
#include "gameevent.h"

class Level
{
    private:
        std::list<GameEvent*> eventList;
        std::string *nextLevel_str; //<-- contains filename of next level
                                    //    (null if this is last level)
    public:
        Level();
        Level(const char *file);
        //void addEvent(int sec, int numEnemy, EnemyShip &enemy);
        //void defineLength(int length);
        bool update(std::list<EnemyShip *> &enemies);
        std::string* getNextLevel() {return nextLevel_str;}
        void cleanUpResources();
};

#endif // LEVEL_H
