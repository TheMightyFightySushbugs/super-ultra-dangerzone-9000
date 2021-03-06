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
               player4(-GAME_WIDTH + 49, 60, 3, QBrush(QColor(70, 128, 162))),
               logo(":/logo.png"),
               game_over(":/game_over.png"),
               paused(":/paused.png")
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
    unsigned int player_1_new_score,
                 player_2_new_score,
                 player_3_new_score,
                 player_4_new_score;

    player_1_new_score = player1.getScore();

    if(playerCount >= 2)
    {
        player_2_new_score = player2.getScore();
    }

    if(playerCount >= 3)
    {
        player_3_new_score = player3.getScore();
    }

    if(playerCount == 4)
    {
        player_4_new_score = player4.getScore();
    }

// update player1 scores
    for(int i = 0; i < 10; i++)
    {
        if(highscores[i] < player_1_new_score)
        {
            unsigned int temp = highscores[i];
            highscores[i] = player_1_new_score;
            player_1_new_score = temp;
        }

        if(highscores[i] == player_1_new_score)
            i = 10;
    }

// update player2 scores
    if(playerCount >= 2)
    {
        for(int i = 0; i < 10; i++)
        {
            if(highscores[i] < player_2_new_score)
            {
                unsigned int temp = highscores[i];
                highscores[i] = player_2_new_score;
                player_2_new_score = temp;
            }

            if(highscores[i] == player_2_new_score)
                i = 10;
        }
    }

// update player3 scores
    if(playerCount >= 3)
    {
        for(int i = 0; i < 10; i++)
        {
            if(highscores[i] < player_3_new_score)
            {
                unsigned int temp = highscores[i];
                highscores[i] = player_3_new_score;
                player_3_new_score = temp;
            }

            if(highscores[i] == player_3_new_score)
                i = 10;
        }
    }

// update player4 scores
    if(playerCount == 4)
    {
        for(int i = 0; i < 10; i++)
        {
            if(highscores[i] < player_4_new_score)
            {
                unsigned int temp = highscores[i];
                highscores[i] = player_4_new_score;
                player_4_new_score = temp;
            }

            if(highscores[i] == player_4_new_score)
                i = 10;
        }
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
    unsigned int player_1_new_score,
                 player_2_new_score,
                 player_3_new_score,
                 player_4_new_score;

    player_1_new_score = player1.getScore();

    if(playerCount >= 2)
    {
        player_2_new_score = player2.getScore();
    }

    if(playerCount >= 3)
    {
        player_3_new_score = player3.getScore();
    }

    if(playerCount == 4)
    {
        player_4_new_score = player4.getScore();
    }

    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 20));
    painter->drawText(-90, -GAME_HEIGHT/2 - 45, "Highest Scores");
    for(int i = 0; i < 10; i++)
    {
        painter->setPen(Qt::white);
        char high_score_str[9];

        if(highscores[i] == player_1_new_score)
        {
            painter->setPen(QColor(225, 128, 162));
            sprintf(high_score_str, "%08u", highscores[i]);
            painter->drawText(-63, -GAME_HEIGHT/3 + 20*i - 10, high_score_str);
        }
        else if(playerCount >= 2 && highscores[i] == player_2_new_score)
        {
            painter->setPen(QColor(34, 69, 111));
            sprintf(high_score_str, "%08u", highscores[i]);
            painter->drawText(-63, -GAME_HEIGHT/3 + 20*i - 10, high_score_str);
        }
        else if(playerCount >= 3 && highscores[i] == player_3_new_score)
        {
            painter->setPen(QColor(225, 54, 162));
            sprintf(high_score_str, "%08u", highscores[i]);
            painter->drawText(-63, -GAME_HEIGHT/3 + 20*i - 10, high_score_str);
        }
        else if(playerCount >= 4 && highscores[i] == player_4_new_score)
        {
            painter->setPen(QColor(70, 128, 162));
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


void Game::cleanUpEnemies()
{
    std::list<EnemyShip*>::iterator currentEnemy = enemies.begin();
    while(currentEnemy != enemies.end())
        delete *currentEnemy++;
    enemies.clear();
}

//Delete everything Game has ever allocated
void Game::cleanUpEverything()
{

    cleanUpEnemies();
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
    if(playerCount >= 2)
    {
        if(player2.getState() != DEAD)
            player2.interpretInput();
        else
            playersStillAlive--;
    }
    if(playerCount >= 3)
    {
        if(player3.getState() != DEAD)
            player3.interpretInput();
        else
            playersStillAlive--;
    }
    if(playerCount == 4)
    {
        if(player4.getState() != DEAD)
            player4.interpretInput();
        else
            playersStillAlive--;
    }

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
                    levelCount++;
                    countdownTimer = 100;
                }
            }
        default:
            break;
    }

    //For every enemy ship...
    unsigned int damage;
    unsigned int numberOfEnemies = enemies.size();
    std::list<EnemyShip*>::iterator currentEnemy = enemies.begin();
    while(numberOfEnemies != 0 && currentEnemy != enemies.end())
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
        {
            damage = (damage | (1 << 31)) + 16;
            EnemyShip::cleanUpEnemyBullets();
        }
        if(player2.isBombing())
        {
            damage = (damage | (1 << 30)) + 16;
            EnemyShip::cleanUpEnemyBullets();
        }
        if(player3.isBombing())
        {
            damage = (damage | (1 << 29)) + 16;
            EnemyShip::cleanUpEnemyBullets();
        }
        if(player4.isBombing())
        {
            damage = (damage | (1 << 28)) + 16;
            EnemyShip::cleanUpEnemyBullets();
        }

        //Check to see if any players are colliding with the current enemy
        if(player1.getState()==ALIVE && player1.collidesWith(**currentEnemy) == true)
        {
            player1.kill();
            damage += 4;
        }
        if(playerCount >= 2 && player2.getState() == ALIVE
           && player2.collidesWith(**currentEnemy) == true)
        {
            player2.kill();
            damage += 4;
        }
        if(playerCount >= 3 && player3.getState() == ALIVE
           && player3.collidesWith(**currentEnemy) == true)
        {
            player3.kill();
            damage += 4;
        }
        if(playerCount == 4 && player4.getState() == ALIVE
           && player4.collidesWith(**currentEnemy) == true)
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
            if((numberOfEnemies = enemies.size()) != 0)
            {
                delete *currentEnemy;
                currentEnemy = enemies.erase(currentEnemy);
            }

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
    if(playerCount >= 2 && player2.getState() == ALIVE)
    {
        damage = EnemyShip::shot(player2);
        if(damage)
            player2.inflictDamage(damage);
    }
    if(playerCount >= 3 && player3.getState() == ALIVE)
    {
        damage = EnemyShip::shot(player3);
        if(damage)
            player3.inflictDamage(damage);
    }
    if(playerCount == 4 && player4.getState() == ALIVE)
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
        {
            painter->drawPixmap(-GAME_WIDTH/2, -3*GAME_HEIGHT/4, GAME_WIDTH, GAME_WIDTH/2, logo);
            painter->fillRect(GAME_WIDTH/4, GAME_HEIGHT/4, GAME_WIDTH/2, GAME_HEIGHT/6, Qt::blue);
            painter->fillRect(GAME_WIDTH/4, GAME_HEIGHT/2, GAME_WIDTH/6, GAME_HEIGHT/6,
                              (playerCount > 1) ? Qt::blue : Qt::gray);
            painter->fillRect(7*GAME_WIDTH/12, GAME_HEIGHT/2, GAME_WIDTH/6, GAME_HEIGHT/6,
                              (playerCount < 4) ? Qt::blue : Qt::gray);
            painter->setPen(Qt::white);
            painter->setFont(QFont("Arial", 12));
            painter->drawText(5*GAME_WIDTH/16, 3*GAME_HEIGHT/8, "New Game");
            painter->drawText(5*GAME_WIDTH/16, 5*GAME_HEIGHT/8, "<");
            painter->drawText(41*GAME_WIDTH/64, 5*GAME_HEIGHT/8, ">");
            painter->setPen(Qt::white);
            painter->setFont(QFont("Arial", 20));
            const char *playerCount_str;
            switch(playerCount)
            {
                case 1: playerCount_str = "1"; break;
                case 2: playerCount_str = "2"; break;
                case 3: playerCount_str = "3"; break;
                case 4: playerCount_str = "4"; break;
                default: playerCount_str = NULL;
            }
            painter->drawText(15*GAME_WIDTH/32, 21*GAME_HEIGHT/32, playerCount_str);
            break;
        }
        case STARTING_LEVEL:
        case PLAYING_LEVEL:
        case PAUSED:
        case ENDING_LEVEL:
        case GAME_OVER:
        {
            player1.draw(painter);
            if(playerCount >= 2) player2.draw(painter);
            if(playerCount >= 3) player3.draw(painter);
            if(playerCount == 4) player4.draw(painter);
            PlayerShip::drawBullets(painter);
            EnemyShip::drawBullets(painter);
            std::list<EnemyShip*>::iterator currentEnemy = enemies.begin();
            while(currentEnemy != enemies.end())
                (*currentEnemy++)->draw(painter);
            Explosion::drawAllExplosions(painter, state != PAUSED);
            player1.drawHUD(painter);
            if(playerCount >= 2) player2.drawHUD(painter);
            if(playerCount >= 3) player3.drawHUD(painter);
            if(playerCount == 4) player4.drawHUD(painter);
            if(state == STARTING_LEVEL)
            {
                char levelIntro_str[10];
                sprintf(levelIntro_str, "Level %u", levelCount);
                painter->setPen(Qt::white);
                painter->setFont(QFont("Arial", 20));
                painter->drawText(-7*GAME_WIDTH/32, -GAME_HEIGHT/6, levelIntro_str);
                if(countdownTimer > 40)
                    painter->drawText(-GAME_WIDTH/4, 0, "READY...");
                else
                    painter->drawText(-GAME_WIDTH/8, 0, "GO!");

            }
            else if(state == ENDING_LEVEL)
            {
                painter->setPen(Qt::white);
                painter->setFont(QFont("Arial", 20));
                painter->drawText(-7*GAME_WIDTH/16, -GAME_HEIGHT/8, "Level Complete");
            }
            else if(state == GAME_OVER)
                painter->drawPixmap(-GAME_WIDTH/2, -GAME_HEIGHT/3, GAME_WIDTH, GAME_WIDTH/2, game_over);
            else if(state == PAUSED)
                painter->drawPixmap(-GAME_WIDTH/2, -GAME_HEIGHT/3, GAME_WIDTH, GAME_WIDTH/2, paused);
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
        //Up button
        case Qt::Key_Up: player1.pressUp(); break;
        case Qt::Key_W:  player2.pressUp(); break;
        case Qt::Key_T:  player3.pressUp(); break;
        case Qt::Key_I:  player4.pressUp(); break;

        //Down button
        case Qt::Key_Down: player1.pressDown(); break;
        case Qt::Key_S:    player2.pressDown(); break;
        case Qt::Key_G:    player3.pressDown(); break;
        case Qt::Key_K:    player4.pressDown(); break;

        //Left button
        case Qt::Key_Left: player1.pressLeft(); break;
        case Qt::Key_A:    player2.pressLeft(); break;
        case Qt::Key_F:    player3.pressLeft(); break;
        case Qt::Key_J:    player4.pressLeft(); break;

        //Right buton
        case Qt::Key_Right: player1.pressRight(); break;
        case Qt::Key_D:     player2.pressRight(); break;
        case Qt::Key_H:     player3.pressRight(); break;
        case Qt::Key_L:     player4.pressRight(); break;

        //Shoot button
        case Qt::Key_Return: player1.pressShoot(); break;
        case Qt::Key_Space: player2.pressShoot(); break;
        case Qt::Key_M:     player3.pressShoot(); break;
        case Qt::Key_Slash: player4.pressShoot(); break;

        //Bomb button
        case Qt::Key_Backslash: player1.pressBomb(); break;
        case Qt::Key_C:         player2.pressBomb(); break;
        case Qt::Key_N:         player3.pressBomb(); break;
        case Qt::Key_Period:    player4.pressBomb(); break;

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

        //Escape button
        case Qt::Key_Escape:
            if(state == PLAYING_LEVEL)
                state = PAUSED;
            else if(state == PAUSED)
                state = PLAYING_LEVEL;
            break;
    }
}

void Game::handleKeyReleaseEvent(int key)
{
    switch(key)
    {
        //Up button
        case Qt::Key_Up: player1.releaseUp(); break;
        case Qt::Key_W:  player2.releaseUp(); break;
        case Qt::Key_T:  player3.releaseUp(); break;
        case Qt::Key_I:  player4.releaseUp(); break;

        //Down button
        case Qt::Key_Down: player1.releaseDown(); break;
        case Qt::Key_S:    player2.releaseDown(); break;
        case Qt::Key_G:    player3.releaseDown(); break;
        case Qt::Key_K:    player4.releaseDown(); break;

        //Left button
        case Qt::Key_Left: player1.releaseLeft(); break;
        case Qt::Key_A:    player2.releaseLeft(); break;
        case Qt::Key_F:    player3.releaseLeft(); break;
        case Qt::Key_J:    player4.releaseLeft(); break;

        //Right buton
        case Qt::Key_Right: player1.releaseRight(); break;
        case Qt::Key_D:     player2.releaseRight(); break;
        case Qt::Key_H:     player3.releaseRight(); break;
        case Qt::Key_L:     player4.releaseRight(); break;
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
        levelCount = 1;
        state = STARTING_LEVEL;
        countdownTimer = 100;
        player1.reset();
        player2.reset();
        player3.reset();
        player4.reset();
    }
    else if(gameYPos >= GAME_HEIGHT/2)
    {
        if(gameXPos <= 5*GAME_WIDTH/12 && playerCount > 1)
            playerCount--;
        if(gameXPos >= 7*GAME_WIDTH/12 && playerCount < 4)
            playerCount++;
    }
}

void Game::setAspectRatio(unsigned int width, unsigned int height)
{
    windowXScale = (int)(GAME_HEIGHT * (double)width / height);
    windowWidth = width;
    windowHeight = height;
}
