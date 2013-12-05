#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <list>
#include "enemyship.h"

enum EventType {TIMED_EVENT, CLEAR_EVENT};

/*! \brief A class that stores the order/structure/design of a game event
 */
class GameEvent
{
    friend class Level;

    private:
        std::list<EnemyShip*> ships;
        EventType type;
        int timer;
    public:
        /**
         * Clean up and delete any resources this instance of GameEvent has allocated
         */
        void cleanUpResources();
};

#endif // GAMEEVENT_H
