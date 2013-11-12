#include "level.h"
//#include <iostream>
//#include <fstream>
/*
Level::Level(std::string &file)
{
    std::ifstream myfile (file.c_str());
      if (myfile.is_open())
      {
        /*** this currently doesn't compile correctly.
         *** EnemyShip doesn't have an operator_>>() function yet.
        while ( std::getline (myfile,line) )  //parsing lines
        {
          cout << line << endl;

          istringstream tokenizer(line);
          string token;

          getline(tokenizer, token, ' ');
          istringstream int_iss(token);
          int sec;
          int_iss >> sec;

          getline(tokenizer, token, ' ');
          istringstream int_iss(token);
          int qtEnemy;
          int_iss >> qtEnemy;

          getline(tokenizer, token, ' ');
          istringstream enemy_iss(token);
          EnemyShip enType;
          enemy_iss >> enType;

          level::addEvent(sec, qtEnemy, enType);
        }
        myfile.close();
      }

      else std::cout << "Unable to open file";
}
*/
Level::Level(void)
{
    GameEvent *asdf = new GameEvent();
    asdf->ships.push_back(new DummyShip(180, -20));
    asdf->ships.push_back(new DummyShip(180, 0));
    asdf->ships.push_back(new DummyShip(180, 20));
    asdf->ships.push_back(new DummyShip(180, 40));
    asdf->type = TIMED_EVENT;
    asdf->timer = 100;
    eventList.push_back(asdf);
    asdf = new GameEvent();
    asdf->ships.push_back(new DummyShip(180, -30));
    asdf->ships.push_back(new DummyShip(180, -15));
    asdf->ships.push_back(new DummyShip(180, 0));
    asdf->ships.push_back(new DummyShip(180, 15));
    asdf->ships.push_back(new DummyShip(180, 30));
    asdf->ships.push_back(new DummyShip(180, 45));
    asdf->type = TIMED_EVENT;
    asdf->timer = 80;
    eventList.push_back(asdf);
    asdf = new GameEvent();
    asdf->ships.push_back(new DummyShip(180, -15));
    asdf->ships.push_back(new DummyShip(180, 0));
    asdf->ships.push_back(new DummyShip(180, 15));
    asdf->ships.push_back(new DummyShip(180, 30));
    asdf->type = TIMED_EVENT;
    asdf->timer = 100;
    eventList.push_back(asdf);
    asdf = new GameEvent();
    asdf->ships.push_back(new DummyShip(180, -30));
    asdf->ships.push_back(new DummyShip(180, -15));
    asdf->ships.push_back(new DummyShip(180, 0));
    asdf->ships.push_back(new DummyShip(180, 15));
    asdf->ships.push_back(new DummyShip(180, 30));
    asdf->ships.push_back(new DummyShip(180, 45));
    asdf->type = TIMED_EVENT;
    asdf->timer = 20;
    eventList.push_back(asdf);
}

//This function is called once every frame, populating the "enemies" list as necessary.
//The return value is 'true' when the end of the level has been reached (to let the game
//know when it should go to the next level), and is 'false' otherwise.
bool Level::update(std::list<EnemyShip*> &enemies)
{
    GameEvent *nextEvent = eventList.front();

    if(eventList.size()==0)
    {
        if(enemies.size()==0)  //end of level reached;
            return true;
    }

    else switch(nextEvent->type)
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
        case CLEAR_EVENT:
            if(enemies.size() == 0){
                eventList.pop_front();

                std::list<EnemyShip*>::iterator currentEnemy = nextEvent->ships.begin();
                while(currentEnemy++ != nextEvent->ships.end())
                    enemies.push_back(*currentEnemy);
                delete nextEvent;
            }
            break;
    }
    return false;
}

/*void Level::addEvent(int sec, int numEnemy, EnemyShip &enemy)
{

}

//void Level::removeEvent

void Level::defineLength(int length)
{

}*/

