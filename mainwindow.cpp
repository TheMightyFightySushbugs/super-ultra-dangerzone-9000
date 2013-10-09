#include "mainwindow.h"
#include "game.h"

#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

MainWindow::MainWindow():QWidget(NULL)
{
    setWindowTitle(tr("Test, test, 1 2 3 ..."));
    setBaseSize(320, 240);
    grabKeyboard();

    gameInstance = new Game();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gameLoop()));
    timer->start(50);
}

void MainWindow::gameLoop()
{
    gameInstance->gameLoop();
    repaint();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    gameInstance->render(&painter, event);
    painter.end();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->isAutoRepeat())
        return;
    gameInstance->handleKeyPressEvent(event->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if(event->isAutoRepeat())
        return;
    gameInstance->handleKeyReleaseEvent(event->key());
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QSize temp = event->size();
    gameInstance->setAspectRatio((double)temp.width()/temp.height());
}
