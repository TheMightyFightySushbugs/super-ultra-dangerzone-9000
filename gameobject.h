#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
    protected:
        int positionX, positionY;
    public:
        virtual void draw();
};

#endif // GAMEOBJECT_H
