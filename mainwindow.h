#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class Game;

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow();

    public slots:
        void gameLoop();

    protected:
        void paintEvent(QPaintEvent * event);
        void keyPressEvent(QKeyEvent * event);
        void keyReleaseEvent(QKeyEvent * event);
        void resizeEvent(QResizeEvent * event);

    private:
        Game * gameInstance;
};

#endif // MAINWINDOW_H
