#include "controller.h"
#include "end.h"
#include "pillar.h"
#include "bird.h"
#include <QGraphicsScene>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QSettings>
#include<QDebug>

Controller::Controller(QGraphicsScene &scene, QObject *parent)
    :QObject(parent)
    ,scene(scene)
    ,pillarHight(0)
{
    newGame();
    connect(&timer, SIGNAL(timeout()),&scene,SLOT(advance()));      //如果放到newGame()函数中，小鸟下落速度会随游戏次数增加而加快。
    connect(&timer,SIGNAL(timeout()), this, SLOT(addPillar()));
    connect(&timer,SIGNAL(timeout()), this, SLOT(birdIsCollided()));
}

void Controller::pause()
{
    if(isPaused){
        timer.start(10);
        isPaused = false;
    }else{              //如果游戏正在运行则停止计时器代表暂停游戏
        timer.stop();
        isPaused = true;
    }
}

void Controller::addPillar()
{   //通过计时符号，每250ms增加一个柱子
    if(!tickCounter)
    {
        pillarHight = randomHight();
        Pillar *pillar1 = new Pillar(0,0,pillarHight);        //上下两个柱子
        Pillar *pillar2 = new Pillar(0,pillarHight+150,600-(pillarHight+150));
        scene.addItem(pillar1);
        scene.addItem(pillar2);

        allPillars.append(pillar1);      //放入柱子栈，超过一定数量时可销毁对象避免内存泄露
        allPillars.append(pillar2);
    }
    if(!allPillars.isEmpty()){
        Pillar *p = allPillars.front();
        if(p&&p->pos().x()==82){
            scoreCounter++;
            emit scoreChanged(scoreCounter);          //分数变一次则发送一次信号
        }
    }

    if(allPillars.count()>4){           //场景中出现第三个个柱子时去掉第一个(已经不显示)
        for(int i=0;i<2;i++){
            Pillar *p = allPillars.front();
            allPillars.pop_front();
            delete p;
        }
    }
    tickCounter = tickCounter > 120 ? 0 : tickCounter+1;

    //通过tickCounterFly控制小鸟在不同是时间段以不同的速度飞行
    if(tickCounterFly<=28){     //每次上升28ms，速度3px/ms
        bird->setSpead(-3);
    }else if(tickCounterFly<=45){
        bird->setSpead(1);
    }else{      //超过45ms则以正常速度落下
        bird->setSpead(4);
    }
    tickCounterFly++;
}

bool Controller::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        keyPressed((QKeyEvent *)event);
        return true;
    }else if(event->type() == QEvent::MouseButtonPress){
        mousePressEvent((QMouseEvent *)event);
        return true;
    }else{
        return QObject::eventFilter(object,event);
    }
}

void Controller::keyPressed(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){
        if(!bird->isCollided())      //鸟没碰撞时接受空格按键
        {
            if(isPaused){
                pause();
            }
            tickCounterFly = 0;
        }
    }
    else if(event->key()==Qt::Key_Escape){
        if(!bird->isCollided()){
            pause();
        }
    }
    else if(event->key()==Qt::Key_Backspace){
        if(bird->isCollided()){
            newGame();
        }
    }
}


void Controller::mousePressEvent(QMouseEvent *event)
{
    if(!bird->isCollided()){
        if(isPaused){
            pause();
        }
        tickCounterFly = 0;
    }
    else if(event->pos().x()>-60&&event->pos().x()<60&&event->pos().y()>40&&event->pos().y()<80){
        newGame();
    }
}


qreal Controller::randomHight() const
{
    return rand()%300+80;
}

void Controller::birdIsCollided()
{
    if(bird->isCollided()){
        gameOver();
    }
}

void Controller::gameOver()
{
    allPillars.clear();
    timer.stop();
    emit gameIsOver(true);

    readSettings();
    highestMark = scoreCounter > highestMark ? scoreCounter : highestMark;
    writesSettings();

    End *w = new End(scoreCounter, highestMark);
    scene.addItem(w);
}

void Controller::newGame()
{
    scene.clear();
    bird = new Bird();
    scene.addItem(bird);
    tickCounter = 0;
    tickCounterFly = 0;
    scoreCounter = 0;
    isPaused = false;

    scene.installEventFilter(this);     //安装事件过滤器

    emit scoreChanged(scoreCounter);
    emit gameIsOver(false);
    pause();
}

void Controller::writesSettings()
{
    QSettings settings("Software inc.", "FlappyBird");  //组织名，应用程序名
    settings.setValue("highestMark",highestMark);
}

void Controller::readSettings()
{
    QSettings settings("Software inc.", "FlappyBird");  //组织名，应用程序名
    highestMark = settings.value("highestMark").toReal();

}
