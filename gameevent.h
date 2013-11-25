#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <list>
#include "enemyship.h"

enum EventType {TIMED_EVENT, CLEAR_EVENT};

class GameEvent
{
    friend class Level;

    private:
        std::list<EnemyShip*> ships;
        EventType type;
        int timer;
    public:
        void cleanUpResources();
};

#endif // GAMEEVENT_H
