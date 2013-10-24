#ifndef GAMEEVENT_H
#define GAMEEVENT_H

enum EventType {TIMED_EVENT, CLEAR_EVENT}

class gameEvent
{
private:
    std::list<EnemyShip*> ships;
    EventType type;
    int timer;
public:
    gameEvent();
};

#endif // GAMEEVENT_H
