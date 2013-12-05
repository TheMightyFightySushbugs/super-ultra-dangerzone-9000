#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class Game;

/*! \brief Main window class of the application. Is responsible for handling handling
 *         button/mouse input, drawing, and updating Game at a fixed interval. (It's
 *         basically a platform-independent intermediary between Game and the outside
 *         world).
 *
 *  Inherits for QWidget from Qt
 */
class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow();

    public slots:
        /**
         * A function triggered every 25 miliseconds which updates the game &
         * redraws the screen.
         */
        void gameLoop();

    protected:
        /**
         * Redraw the window as necessary
         */
        void paintEvent(QPaintEvent * event);

        /**
         * Handles key presses & forwards the information to Game
         *
         * @param event A QKeyEvent describing what key was pressed
         */
        void keyPressEvent(QKeyEvent * event);

        /**
         * Handles key releases & forwards the information to Game
         *
         * @param event A QKeyEvent describing what key was released
         */
        void keyReleaseEvent(QKeyEvent * event);

        /**
         * Handles mouse clicks & forwards the information to Game
         *
         * @param event A QKeyEvent describing what mouse button was clicked
         */
        void mousePressEvent(QMouseEvent *event);

        /**
         * Notifies Game whenever the window is resized
         *
         * @param event A QResizedEvent describing the window's new size
         */
        void resizeEvent(QResizeEvent * event);

    private:
        Game * gameInstance;
};

#endif // MAINWINDOW_H
