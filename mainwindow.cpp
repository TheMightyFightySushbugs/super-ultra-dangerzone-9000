#include "mainwindow.h"
#include "game.h"

#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

MainWindow::MainWindow():QWidget(NULL)
{
    setWindowTitle(tr("super-ultra-dangerzone-9000"));
    setBaseSize(320, 240);
    //grabKeyboard();

    gameInstance = new Game();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gameLoop()));
    timer->start(25);
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
    //painter.setRenderHint(QPainter::Antialiasing);
    gameInstance->render(&painter);
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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    gameInstance->handleMouseClick(event->x(), event->y());
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QSize windowSize = event->size();
    gameInstance->setAspectRatio(windowSize.width(), windowSize.height());
}
