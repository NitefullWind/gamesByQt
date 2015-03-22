#ifndef CONTROLLER
#define CONTROLLER
#include <QObject>
#include <QTimer>

class QGraphicsScene;
class QKeyEvent;
class QMouseEvent;
class Pillar;
class Bird;

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QGraphicsScene &scene, QObject *parent = 0);
    QTimer timer;
signals:
    void scoreChanged(const int &score) const;      //自定义信号，发送新的分数
    void gameIsOver(const bool is) const;
public slots:
    void pause();
    void addPillar();
    void birdIsCollided();
private:
    int tickCounter, tickCounterFly;
    QGraphicsScene &scene;
    QList<Pillar *> allPillars;
    Bird *bird;
    qreal randomHight() const;
    qreal pillarHight, birdHight, scoreCounter, highestMark;
    bool isPaused;
    void keyPressed(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void gameOver();
    void newGame();
    void writesSettings();
    void readSettings();

protected:
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // CONTROLLER

