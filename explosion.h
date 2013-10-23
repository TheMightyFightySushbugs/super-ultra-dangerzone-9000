#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"

class Explosion : public GameObject
{
    private:
        static  std::vector<Explosion*> explosions;
        int timeRemaining;
        Explosion(int _positionX, int _positionY, int _radius, int _time, QBrush &_color);
    public:
        void draw(QPainter *painter);
        static void drawAllExplosions(QPainter *painter);
        static void addExplosion(int _positionX, int _positionY, int _radius,
                                 int _time, QBrush &_color);
        virtual ~Explosion() {}
};

#endif // EXPLOSION_H
