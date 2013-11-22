#include "game.h"
#include "playership.h"

#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <fstream>

std::list<EnemyShip*> Game::enemies;

Game::Game() : player1(-GAME_WIDTH + 49, -30, 0, QBrush(QColor(225, 128, 162))),
               player2(-GAME_WIDTH + 49, 0, 1, QBrush(QColor(34, 69, 111))),
               player3(-GAME_WIDTH + 49, 30, 2, QBrush(QColor(225, 54, 162))),
               player4(-GAME_WIDTH + 49, 60, 3, QBrush(QColor(70, 128, 162)))
{
    state = MAIN_MENU;
    playerCount = 4;
    readHighscoreFile();
}

void Game::readHighscoreFile()
{
    for(int i = 0; i < 10; i++)
        highscores[i] = 0;

    std::fstream high_score_file;

    high_score_file.open("highscores.txt");

    if(high_score_file.good())
    {
        unsigned int value;
        for(int i = 0; i < 10; i++)
        {
            high_score_file >> value;
            highscores[i] = value;
        }
    }

    high_score_file.close();
    //[to-do] initialize highscore array with values from highscore file
}

void Game::updateHighscores()
{
    unsigned int new_score = player1.getScore();
    for(int i = 0; i < 10; i++)
    {
        if(highscores[i] < new_score)
        {
            unsigned int temp = highscores[i];
            highscores[i] = new_score;
            new_score = temp;
        }

        if(highscores[i] == new_score)
            i = 10;
    }

    std::ofstream outStream;

    outStream.open("highscores.txt");
    for(int i = 0; i < 10; i++)
    {
        outStream << highscores[i] << std::endl;
    }

    outStream.close();
    //[to-do] update highscore array if any player has beaten a highscore
}

void Game::displayHighscores(QPainter *painter)
{
    unsigned int new_score = player1.getScore();
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 20));
    painter->drawText(-90, -GAME_HEIGHT/2 - 45, "Highest Scores");
    for(int i = 0; i < 10; i++)
    {
        painter->setPen(Qt::white);
        char high_score_str[9];

        if(highscores[i] == new_score)
        {
            painter->setPen(Qt::blue);
            sprintf(high_score_str, "%08u", highscores[i]);
            painter->drawText(-63, -GAME_HEIGHT/3 + 20*i - 10, high_score_str);
        }
        else
        {
            sprintf(high_score_str, "%08u", highscores[i]);
            painter->drawText(-63, -GAME_HEIGHT/3 + 20*i - 10, high_score_str);
        }
    }

    //[to-do] display highscores
}


//Delete everything Game has ever allocated
void Game::cleanUpEverything()
{

    std::list<EnemyShip*>::iterator currentEnemy = enemies.begin();
    while(currentEnemy != enemies.end())
        delete *currentEnemy++;
    enemies.clear();
    PlayerShip::cleanUpPlayerBullets();
    EnemyShip::cleanUpEnemyBullets();
    Explosion::cleanUpExplosions();
    if(currentLevel != NULL)
    {
        currentLevel->cleanUpResources();
        delete currentLevel;
    }
}

void Game::gameLoop()
{
    if(state == PAUSED || state == MAIN_MENU || state == HIGH_SCORE_DISPLAY)
        return;

    int playersStillAlive = playerCount;

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
    {
        state = GAME_OVER;
        countdownTimer = 100;
        std::cout << "everyone is dead now..." << std::endl;
    }

    PlayerShip::moveBullets();
    EnemyShip::moveBullets();

    switch(state)
    {
        case STARTING_LEVEL:
            if(--countdownTimer == 0)
                state = PLAYING_LEVEL;
            break;
        case GAME_OVER:
            if(--countdownTimer == 0)
            {
                std::cout << "Game Over! (countdownTimer timed out)" << std::endl;
                cleanUpEverything();
                state = HIGH_SCORE_DISPLAY;
                countdownTimer = 120;
                updateHighscores();
                break;
            }
            //odd placement of break statement is intentional; this is a fall-through case
        case PLAYING_LEVEL:
            if(currentLevel->update(enemies) == true && state == PLAYING_LEVEL)
            {
                //Store filename of next level, then delete current level
                if(levelFileName != NULL)
                    delete levelFileName;
                levelFileName = currentLevel->getNextLevel();
                delete currentLevel;
                currentLevel = NULL;
                std::cout << "Moving onto next level..." << std::endl;
                state = ENDING_LEVEL;
                countdownTimer = 100;
            }
            break;
        case ENDING_LEVEL:
            if(--countdownTimer == 0)
            {
                if(levelFileName == NULL)
                {
                    std::cout << "Game Complete! You Win!" << std::endl;
                    cleanUpEverything();
                    state = HIGH_SCORE_DISPLAY;
                    countdownTimer = 120;
                    updateHighscores();
                }
                else
                {
                    currentLevel = new Level(levelFileName->c_str());
                    state = STARTING_LEVEL;
                    countdownTimer = 100;
                }
            }
        default:
            break;
    }

    //For every enemy ship...
    unsigned int damage;
    std::list<EnemyShip*>::iterator currentEnemy = enemies.begin();
    while(currentEnemy != enemies.end())
    {

        //Let the ship do whatever it has to do (move/shoot/etc)
        //Delete it if it goes out of bounds
        if((*currentEnemy)->move()==true)
        {
            delete *currentEnemy;
            currentEnemy=enemies.erase(currentEnemy);
            continue;
        }

        damage = 0;
        //Check to see if any player is currently bombing
        if(player1.isBombing())
            damage = (damage | (1 << 31)) + 16;
        if(player2.isBombing())
            damage = (damage | (1 << 30)) + 16;
        if(player3.isBombing())
            damage = (damage | (1 << 29)) + 16;
        if(player4.isBombing())
            damage = (damage | (1 << 28)) + 16;

        //Check to see if any players are colliding with the current enemy
        if(player1.getState()==ALIVE && player1.collidesWith(**currentEnemy) == true)
        {
            player1.kill();
            damage += 4;
        }
        if(player2.getState()==ALIVE && player2.collidesWith(**currentEnemy) == true)
        {
            player2.kill();
            damage += 4;
        }
        if(player3.getState()==ALIVE && player3.collidesWith(**currentEnemy) == true)
        {
            player3.kill();
            damage += 4;
        }
        if(player4.getState()==ALIVE && player4.collidesWith(**currentEnemy) == true)
        {
            player4.kill();
            damage += 4;
        }
        //Check to see if any of the player's bullets hit the ship
        damage += PlayerShip::shot(**currentEnemy);

        //If any bullets did hit, and they inflicted enough damage to destroy the ship...
        unsigned int pointsEarned;
        if(damage && (pointsEarned = (*currentEnemy)->inflictDamage(damage)))
        {
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

void Game::render(QPainter *painter)
{
    painter->setWindow(-windowXScale, -GAME_HEIGHT, windowXScale*2, GAME_HEIGHT*2);
    painter->save();
    painter->fillRect(-GAME_WIDTH, -GAME_HEIGHT, GAME_WIDTH*2, GAME_HEIGHT*2, Qt::black);
    switch(state)
    {
        case MAIN_MENU:
            painter->fillRect(GAME_WIDTH/4, GAME_HEIGHT/4, GAME_WIDTH/2, GAME_HEIGHT/6, Qt::blue);
            painter->fillRect(GAME_WIDTH/4, GAME_HEIGHT/2, GAME_WIDTH/2, GAME_HEIGHT/6, Qt::blue);
            break;
        case STARTING_LEVEL:
        case PLAYING_LEVEL:
        case PAUSED:
        case ENDING_LEVEL:
        case GAME_OVER:
        {
            player1.draw(painter);
            player2.draw(painter);
            player3.draw(painter);
            player4.draw(painter);
            PlayerShip::drawBullets(painter);
            EnemyShip::drawBullets(painter);
            std::list<EnemyShip*>::iterator currentEnemy = enemies.begin();
            while(currentEnemy != enemies.end())
                (*currentEnemy++)->draw(painter);
            Explosion::drawAllExplosions(painter, state != PAUSED);
            player1.drawHUD(painter);
            player2.drawHUD(painter);
            player3.drawHUD(painter);
            player4.drawHUD(painter);
            if(state == GAME_OVER)
                painter->fillRect(-GAME_WIDTH/2, -GAME_HEIGHT/3, GAME_WIDTH, GAME_WIDTH/2, Qt::blue);
            if(state == PAUSED)
                painter->fillRect(-GAME_WIDTH/2, -GAME_HEIGHT/3, GAME_WIDTH, GAME_WIDTH/2, Qt::green);
            break;
        }
        case HIGH_SCORE_DISPLAY:
            displayHighscores(painter);
            if(--countdownTimer == 0)
                state = MAIN_MENU;
            break;
    }
    painter->restore();
}

void Game::handleKeyPressEvent(int key)
{
    if(state == MAIN_MENU)
        return;

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
        case Qt::Key_B:
            player1.pressBomb();
            player2.pressBomb();
            player3.pressBomb();
            player4.pressBomb();
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
        case Qt::Key_Escape:
            if(state == PLAYING_LEVEL)
                state = PAUSED;
            else if(state == PAUSED)
                state = PLAYING_LEVEL;
            break;
    }
}

void Game::handleMouseClick(int xPos, int yPos)
{
    if(state != MAIN_MENU)
        return;

    //translate absolute mouse coordinates into game-relative coordinates
    int gameXPos = (int)((2.0 * xPos / windowWidth - 1) * windowXScale);
    if(gameXPos < GAME_WIDTH/4 || gameXPos > 3*GAME_WIDTH/4)
        return;
    int gameYPos = (int)((2.0 * yPos / windowHeight - 1) * GAME_HEIGHT);
    if(gameYPos < GAME_HEIGHT/4 || gameYPos > 2*GAME_HEIGHT/3)
        return;

    if(gameYPos <= 5*GAME_HEIGHT/12)
    {
        currentLevel = new Level("level1.txt");
        levelFileName = NULL;
        state = STARTING_LEVEL;
        countdownTimer = 100;
        playerCount = 4;
        player1.reset();
        player2.reset();
        player3.reset();
        player4.reset();
    }
    else if(gameYPos >= GAME_HEIGHT/2)
        std::cout << "This button doesn't do anything yet..." << std::endl;
}

void Game::setAspectRatio(unsigned int width, unsigned int height)
{
    windowXScale = (int)(GAME_HEIGHT * (double)width / height);
    windowWidth = width;
    windowHeight = height;
}
