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
        /**
         * Constructor for Level
         *
         * @param File a text file that contains the instructions for the level
         */
        Level(const char *file);
        //void addEvent(int sec, int numEnemy, EnemyShip &enemy);
        //void defineLength(int length);
        /**
         * Populates the enemies list
         *
         * @param enemies a list of type EnemyShip
         */
        bool update(std::list<EnemyShip *> &enemies);
        /**
         * Returns the pointer to the NextLevel
         */
        std::string* getNextLevel() {return nextLevel_str;}
        /**
         * Cleans the list of events
         */
        void cleanUpResources();
};

#endif // LEVEL_H
