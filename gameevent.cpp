#include "gameevent.h"

void GameEvent::cleanUpResources()
{
    std::list<EnemyShip*>::iterator currentShip = ships.begin();
    while(currentShip != ships.end())
        delete *currentShip++;
}
