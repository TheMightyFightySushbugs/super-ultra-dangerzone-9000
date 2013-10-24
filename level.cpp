#include "level.h"
#include <iostream>
#include <fstream>

level::level(std::string &file)
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
        }*/
        myfile.close();
      }

      else std::cout << "Unable to open file";
}

level::level()
{
    //create an empty list of events
}

level::update(){
    GameEvent nextEvent = new GameEvent;
    nextEvent = eventList.front;
    switch(nextEvent.type){
        case TIMED_EVENT:
            if(nextEvent.timer <= 0){
                pop_front(eventList);
                //store some place else
                //add event to game
            }
        case CLEAR_EVENT
    //if(nextEvent.ships.size() == 0){  reference list inside game.h
                //same thing
               // pop_front(eventList);
           // }

    }
}

void level::addEvent(int sec, int numEnemy, EnemyShip &enemy)
{

}

void level::defineLength(int length)
{

}
//void level::removeEvent
//void level::update(

