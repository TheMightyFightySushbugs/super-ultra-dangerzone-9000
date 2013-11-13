#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"

class Explosion : public GameObject
{
    private:
        static  std::list<Explosion*> explosions;
        int timeRemaining;
        Explosion(int _positionX, int _positionY, int _radius, int _time, QBrush &_color);
    public:
        static void drawAllExplosions(QPainter *painter, const bool updateTimers);
        static void addExplosion(int _positionX, int _positionY, int _radius,
                                 int _time, QBrush &_color);
        static void cleanUpExplosions();
        virtual ~Explosion() {}
};

#endif // EXPLOSION_H
