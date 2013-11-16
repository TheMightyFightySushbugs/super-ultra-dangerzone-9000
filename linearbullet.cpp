#include "linearbullet.h"
#include <QPainter>

LinearBullet::LinearBullet(int _positionX, int _positionY, int _velocityX, int _velocityY,
                           unsigned int _playerID, QBrush &_color)
    : Bullet(_positionX, _positionY, 3, 1, _playerID, _color)
{
    velocityX = _velocityX;
    velocityY = _velocityY;
}

bool LinearBullet::move()
{
    positionX += velocityX;
    if(positionX < -GAME_WIDTH - width || positionX > GAME_WIDTH + width)
        return true;
    positionY += velocityY;
    if(positionY < -GAME_HEIGHT - height || positionY > GAME_HEIGHT + height)
        return true;
    return false;
}

QBrush peaGreen = QBrush(QColor(105, 200, 105));
