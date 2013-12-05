#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"

/*!
 * \brief A class used to represent an explosion
 */
class Explosion : public GameObject
{
    private:
        static  std::list<Explosion*> explosions;
        int timeRemaining;
        Explosion(int _positionX, int _positionY, int _radius, int _time, QBrush &_color);
    public:
        /**
         * Draw every explosion
         * @param painter A QPainter object with which to paint
         * @param updateTimers If true, decrement each explosion's countdown timer by 1.
         *                     Otherwise, don't.
         */
        static void drawAllExplosions(QPainter *painter, const bool updateTimers);

        /**
         * Create a new explosion
         * @param _positionX Explosion's initial X coordinate
         * @param _positionY Explosion's initial Y coordinate
         * @param _radius Explosion's radius
         * @param _time How many frames the explosion will last
         * @param _color What color the explosion will be
         */
        static void addExplosion(int _positionX, int _positionY, int _radius,
                                 int _time, QBrush &_color);

        /**
         * Clean up & delete all explosions
         */
        static void cleanUpExplosions();
        virtual ~Explosion() {}
};

#endif // EXPLOSION_H
