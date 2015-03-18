#ifndef CONTROLLER
#define CONTROLLER
#include <QObject>
#include <QTimer>

class QGraphicsScene;
class QKeyEvent;
class Map;
class Bird;

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QGraphicsScene &scene, QObject *parent = 0);
    QTimer timer;
signals:
    void scoreChanged(const int &score) const;      //自定义信号，发送新的分数
    void gameIsOver() const;              //游戏结束信号
public slots:
    void pause();
    void resume();
    void addPillar();
    void birdIsCollided();
private:
    int tickCounter, tickCounterFly, scoreCounter;
    QGraphicsScene &scene;
    QList<Map *> allPillars;
    Bird *bird;
    qreal randomHight() const;
    qreal pillarHight, birdHight;
    bool isPaused;
    void keyPressed(QKeyEvent *event);
    void gameOver();
protected:
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // CONTROLLER

