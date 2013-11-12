#include "game.h"
#include "playership.h"

#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

Game::Game() : player1(-111, -30, 0, QBrush(QColor(225, 128, 162))),
               player2(-111, 0, 1, QBrush(QColor(34, 69, 111))),
               player3(-111, 30, 2, QBrush(QColor(225, 54, 162))),
               player4(-111, 60, 3, QBrush(QColor(70, 128, 162)))
{
    windowHeight = 120;
    windowWidth = 160;
    background = QBrush(QColor(14, 32, 24));
    state = PLAYING_LEVEL; //<-- MAIN_MENU isn't implemented yet

    currentLevel = new Level();
}

void Game::gameLoop()
{
    if(state == PAUSED)
        return;

    int playersStillAlive = 4;

    //Let the players do whatever they have to do (move/shoot/etc)
    if(player1.getState() != DEAD)
        player1.interpretInput();
    else
        playersStillAlive--;
    if(player2.getState() != DEAD)
        player2.interpretInput();
    else
        playersStillAlive--;
    if(player3.getState() != DEAD)
        player3.interpretInput();
    else
        playersStillAlive--;
    if(player4.getState() != DEAD)
        player4.interpretInput();
    else
        playersStillAlive--;

    if(state == PLAYING_LEVEL && playersStillAlive <= 0)
        state = GAME_OVER;

    PlayerShip::moveBullets();

    std::cout << state << std::endl;
    if(state == PLAYING_LEVEL && currentLevel->update(enemies) == true)
    {
        //figure out what file the next level is stored in...
        //store that filename somewhere...
        delete currentLevel;
        state = ENDING_LEVEL;
    }

    std::cout << "after update()" << std::endl;

    //For every enemy ship...
    unsigned int damage;
    std::list<EnemyShip*>::iterator currentEnemy = enemies.begin();
    while(enemies.size() > 0 && currentEnemy != enemies.end())
    {

        std::cout << "handling ship, enemies.size() == " << enemies.size() << std::endl;

        //Let the ship do whatever it has to do (move/shoot/etc)
        //checks for out of bounds
        if((*currentEnemy)->move()==true)
        {
            std::cout << "destroying ship (ship left screen)" << std::endl;
            delete *currentEnemy;
            currentEnemy=enemies.erase(currentEnemy);
            continue;
        }

        //if player exist
        //if player is alive
        //checking for collision
        damage = 0;
        if(player1.getState()==ALIVE && player1.collidesWith(**currentEnemy) == true)
        {
            player1.kill();
            damage += 47;
        }
        if(player2.getState()==ALIVE && player2.collidesWith(**currentEnemy) == true)
        {
            player2.kill();
            damage += 47;
        }
        if(player3.getState()==ALIVE && player3.collidesWith(**currentEnemy) == true)
        {
            player3.kill();
            damage += 47;
        }
        if(player4.getState()==ALIVE && player4.collidesWith(**currentEnemy) == true)
        {
            player4.kill();
            damage += 47;
        }
        //Check to see if any of the player's bullets hit the ship
        damage += PlayerShip::shot(**currentEnemy);

        //If any bullets did hit, and they inflicted enough damage to destroy the ship...
        unsigned int pointsEarned;
        if(damage && (pointsEarned = (*currentEnemy)->inflictDamage(damage)))
        {
            std::cout << "destroying ship (shot)" << std::endl;
            //...then go ahead and destroy the ship
            delete *currentEnemy;
            currentEnemy = enemies.erase(currentEnemy);
            if(state != GAME_OVER)
            {
                if(pointsEarned & 0x80000000)
                    player1.incrementScore(pointsEarned & 0x0FFFFFFF);
                if(pointsEarned & 0x40000000)
                    player2.incrementScore(pointsEarned & 0x0FFFFFFF);
                if(pointsEarned & 0x20000000)
                    player3.incrementScore(pointsEarned & 0x0FFFFFFF);
                if(pointsEarned & 0x10000000)
                    player4.incrementScore(pointsEarned & 0x0FFFFFFF);
            }
        }
        else //Otherwise, move onto the next one
            currentEnemy++;
    }

    if(state == GAME_OVER)
        return;

    //Don't bother checking for collisions in player isn't currently alive
    if(player1.getState() == ALIVE)
    {
        //Check to see if any enemy bullets hit player 1
        damage = EnemyShip::shot(player1);

        //If any bullets did hit, inflict damage onto player
        if(damage)
            player1.inflictDamage(damage);
    }
    if(player2.getState() == ALIVE)
    {
        damage = EnemyShip::shot(player2);
        if(damage)
            player2.inflictDamage(damage);
    }
    if(player3.getState() == ALIVE)
    {
        damage = EnemyShip::shot(player3);
        if(damage)
            player3.inflictDamage(damage);
    }
    if(player4.getState() == ALIVE)
    {
        damage = EnemyShip::shot(player4);
        if(damage)
            player4.inflictDamage(damage);
    }
}

void Game::render(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(), background);
    painter->setWindow(-windowWidth, -windowHeight, windowWidth*2, windowHeight*2);
    painter->save();
    painter->fillRect(-160, -120, 320, 240, Qt::yellow);
    player1.draw(painter);
    player2.draw(painter);
    player3.draw(painter);
    player4.draw(painter);
    PlayerShip::drawBullets(painter);
    std::list<EnemyShip*>::iterator currentEnemy = enemies.begin();
    while(currentEnemy != enemies.end())
        (*currentEnemy++)->draw(painter);
    Explosion::drawAllExplosions(painter, state != PAUSED);
    player1.drawHUD(painter);
    player2.drawHUD(painter);
    player3.drawHUD(painter);
    player4.drawHUD(painter);
    if(state == GAME_OVER)
        painter->fillRect(-80, -40, 160, 80, Qt::blue);
    if(state == PAUSED)
        painter->fillRect(-80, -40, 160, 80, Qt::green);
    painter->restore();
}

void Game::handleKeyPressEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
            player1.pressUp();
            player2.pressUp();
            player3.pressUp();
            player4.pressUp();
            break;
        case Qt::Key_Down:
            player1.pressDown();
            player2.pressDown();
            player3.pressDown();
            player4.pressDown();
            break;
        case Qt::Key_Left:
            player1.pressLeft();
            player2.pressLeft();
            player3.pressLeft();
            player4.pressLeft();
            break;
        case Qt::Key_Right:
            player1.pressRight();
            player2.pressRight();
            player3.pressRight();
            player4.pressRight();
            break;
        case Qt::Key_Space:
            player1.pressShoot();
            player2.pressShoot();
            player3.pressShoot();
            player4.pressShoot();
            break;
        //Just to demonstrate that PlayerShip::kill() is working...
        case Qt::Key_1:
            if(player1.getState() == ALIVE)
                player1.kill();
            break;
        case Qt::Key_2:
            if(player2.getState() == ALIVE)
                player2.kill();
            break;
        case Qt::Key_3:
            if(player3.getState() == ALIVE)
                player3.kill();
            break;
        case Qt::Key_4:
            if(player4.getState() == ALIVE)
                player4.kill();
            break;
    }
}

void Game::handleKeyReleaseEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
            player1.releaseUp();
            player2.releaseUp();
            player3.releaseUp();
            player4.releaseUp();
            break;
        case Qt::Key_Down:
            player1.releaseDown();
            player2.releaseDown();
            player3.releaseDown();
            player4.releaseDown();
            break;
        case Qt::Key_Left:
            player1.releaseLeft();
            player2.releaseLeft();
            player3.releaseLeft();
            player4.releaseLeft();
            break;
        case Qt::Key_Right:
            player1.releaseRight();
            player2.releaseRight();
            player3.releaseRight();
            player4.releaseRight();
            break;
        case Qt::Key_Space:
            player1.releaseShoot();
            player2.releaseShoot();
            player3.releaseShoot();
            player4.releaseShoot();
            break;
        case Qt::Key_Escape:
            if(state == PLAYING_LEVEL)
                state = PAUSED;
            else if(state == PAUSED)
                state = PLAYING_LEVEL;
            break;
    }
}

void Game::setAspectRatio(double newAspectRatio)
{
    windowWidth = (int)(windowHeight*newAspectRatio);
}
