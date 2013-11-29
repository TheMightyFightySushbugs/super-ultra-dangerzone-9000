#include "level.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
Level::Level(const char *file)
{
    string typeEvent;
    string positionY;
    string seconds;
    string typeEnemy;
    string quantity;
    int posY;
    int sec;
    int qty;
    int i;

    cout << "Opening \"" << file << "\"" << endl;
    ifstream myfile (file);
    if (myfile.fail())
    {
        cout << "Unable to open \"" << file << "\"" << endl;
        return;
    }

    nextLevel_str = NULL;
    while(myfile.eof()==0){
        getline(myfile, typeEvent, ' ');
        if(typeEvent.size() == 0)
        {
            std::cout << "blank line" << std::endl;
            continue; //go back to start of the loop
        }

        std::cout << "allocating new event" << std::endl;
        GameEvent *event = new GameEvent();

        std::cout << "\"" << typeEvent << "\"" << std::endl;
        if(typeEvent.compare("TIMED_EVENT") == 0){
            std::cout << "type: TIMED_EVENT" << std::endl;
            event->type = TIMED_EVENT;
            getline(myfile, seconds, ' ');
            sec = atoi(seconds.c_str());
            std::cout << "time: " << sec << std::endl;
            event->timer = sec;
        }
        else if (typeEvent.compare("CLEAR_EVENT") == 0)
        {
            std::cout << "type: CLEAR_EVENT" << std::endl;
            event->type = CLEAR_EVENT;
        }
        else
            nextLevel_str = new string(typeEvent.substr(0, typeEvent.find('\n')));

        getline(myfile, quantity, '\n');
        qty = atoi(quantity.c_str());
        std::cout << "quantity " << qty << endl;



        for(i=0;i<qty;i++){
            getline(myfile,typeEnemy, ' ');
            getline(myfile,typeEnemy, ' ');
            getline(myfile,typeEnemy, ' ');
            getline(myfile,typeEnemy, ' ');
            getline(myfile,typeEnemy, ' ');

            getline(myfile,positionY, '\n');
            posY = atoi(positionY.c_str());
            if(typeEnemy.compare("DummyShip")==0)
            {
                event->ships.push_back(new DummyShip(posY));
                std::cout << "creating dummyship at posititon: " << posY << std::endl;
            }
            else if (typeEnemy.compare("ZigZagShip")==0){
                event->ships.push_back(new ZigZagShip(posY));
                std::cout << "creating ZigZagShip at posititon: " << posY << std::endl;
            }
            else if (typeEnemy.compare("SpawnerShip")==0){
                event->ships.push_back(new SpawnerShip(posY));
                std::cout << "creating SpawnerShip at posititon: " << posY << std::endl;
            }
            else if (typeEnemy.compare("StraightShip")==0){
                event->ships.push_back(new StraightShip(posY));
                std::cout << "creating StraightShip at posititon: " << posY << std::endl;
            }
            else if (typeEnemy.compare("DiverShip")==0){
                event->ships.push_back(new DiverShip(posY));
                std::cout << "creating DiverShip at posititon: " << posY << std::endl;
            }
            else if (typeEnemy.compare("SideShotShip")==0){
                event->ships.push_back(new SideShotShip(posY));
                std::cout << "creating SideShotShip at posititon: " << posY << std::endl;
            }
        }
        getline(myfile,typeEnemy, '\n');
        std::cout << "calling push back event" << std::endl;
        eventList.push_back(event);
   }
    myfile.close();
}

//This function is called once every frame, populating the "enemies" list as necessary.
//The return value is 'true' when the end of the level has been reached (to let the game
//know when it should go to the next level), and is 'false' otherwise.
bool Level::update(std::list<EnemyShip*> &enemies)
{
    if(eventList.size()==0)
        return (enemies.size() == 0);  //true if end of level reached

    GameEvent *nextEvent = eventList.front();

    switch(nextEvent->type)
    {
        case TIMED_EVENT:
            if(nextEvent->timer-- <= 0) //decrements the timer
            {
                //Remove the event from the eventList
                eventList.pop_front();

                std::list<EnemyShip*>::iterator currentEnemy = nextEvent->ships.begin();
                while(currentEnemy != nextEvent->ships.end())
                    enemies.push_back(*currentEnemy++);
                delete nextEvent;
            }
            break;
        case CLEAR_EVENT:
            if(enemies.size() == 0)
            {
                eventList.pop_front();

                std::list<EnemyShip*>::iterator currentEnemy = nextEvent->ships.begin();
                while(currentEnemy != nextEvent->ships.end())
                    enemies.push_back(*currentEnemy++);
                delete nextEvent;
            }
            break;
    }
    return false;
}

void Level::cleanUpResources()
{
    std::list<GameEvent*>::iterator currentEvent = eventList.begin();
    while(currentEvent != eventList.end())
    {
        (*currentEvent)->cleanUpResources();
        delete *currentEvent++;
    }
}

/*void Level::addEvent(int sec, int numEnemy, EnemyShip &enemy)
{

}

//void Level::removeEvent

void Level::defineLength(int length)
{

}*/

