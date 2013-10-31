#include "level.h"
#include <iostream>
#include <fstream>

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
        }*/
        myfile.close();
      }

      else std::cout << "Unable to open file";
}

Level::Level()
{
    //create an empty list of events
}

//This function is called once every frame, populating the "enemies" list as necessary.
//The return value is 'true' when the end of the level has been reached (to let the game
//know when it should go to the next level), and is 'false' otherwise.
bool Level::update(std::list<EnemyShip *> &enemies)
{
    GameEvent *nextEvent = eventList.front();

    if(nextEvent->timer == 0)  //end of level reached;
        return true;

    switch(nextEvent->type)
    {
        case TIMED_EVENT:
            if(nextEvent->timer <= 0)
            {
                //Remove the event from the eventList
                eventList.pop_front();

                unsigned int damage;
                std::list<EnemyShip*>::iterator currentEnemy = nextEvent->ships.begin();
                while(currentEnemy != nextEvent->ships.end())
                {
                    enemies.add(currentEnemy);
                    //Let the ship do whatever it has to do (move/shoot/etc)
                    (*currentEnemy)->move();

                    //[to-do: check when enemies go out of bounds. delete them when they do]

                    //Check to see if any of the player's bullets hit the ship
                    damage = PlayerShip::shot(**currentEnemy);

                    //If any bullets did hit, and they inflicted enough damage to destroy the ship...
                    unsigned int pointsEarned;
                    if(damage && (pointsEarned = (*currentEnemy)->inflictDamage(damage)))
                    {
                        //...then go ahead and destroy the ship
                        delete *currentEnemy;
                        currentEnemy = enemies.erase(currentEnemy);
                        player1.incrementScore(pointsEarned & 0x0FFFFFFF);
                    }
                    else //Otherwise, move onto the next one
                        currentEnemy++;
                }
                //We still have a pointer to the removed event (nextEvent)
                //... now we must add the event to the game...
            }
        case CLEAR_EVENT:
            if(enemies.size() == 0){
                eventList.pop_front();
            }
            break;
    }
}

void Level::addEvent(int sec, int numEnemy, EnemyShip &enemy)
{

}

//void Level::removeEvent

void Level::defineLength(int length)
{

}

