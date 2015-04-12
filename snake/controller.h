#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsScene>

#include "food.h"
#include "wall.h"
#include "snake.h"
#include "end.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QGraphicsScene &scene, QObject *parent = 0);
    ~Controller();
private:
    QGraphicsScene &scene;
    Wall *wall[4];
    Snake *snake[2];
    Food *food;
    End *end;

    QTimer timer;
    bool gameIsPause;
    void pause();
    void keyPress(QKeyEvent *event);

    void drawWall();
    void drawSnake();
    void drawFood();

    void newGame();

    bool gameIsOver;
    void gameOver(QString winner);
private slots:
    void checkCollisions();
protected:
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // CONTROLLER_H
