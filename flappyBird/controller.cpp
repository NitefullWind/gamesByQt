#include "controller.h"
#include "map.h"
#include "bird.h"
#include <QGraphicsScene>
#include <QEvent>
#include <QKeyEvent>
#include <QLabel>
#include<QDebug>

Controller::Controller(QGraphicsScene &scene, QObject *parent)
    :QObject(parent)
    ,scene(scene)
    ,bird(new Bird())
    ,tickCounter(0)
    ,tickCounterFly(0)
    ,scoreCounter(0)
    ,pillarHight(0)
    ,isPaused(false)
{
    scene.addItem(bird);
    scene.installEventFilter(this);     //安装事件过滤器

    timer.start(10);
    connect(&timer,SIGNAL(timeout()), this, SLOT(addPillar()));
    connect(&timer,SIGNAL(timeout()), this, SLOT(birdIsCollided()));
    pause();
    resume();
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

void Controller::resume()
{
    connect(&timer, SIGNAL(timeout()),&scene,SLOT(advance()));
}

void Controller::addPillar()
{   //通过计时符号，每250ms增加一个柱子
    if(!tickCounter)
    {
        pillarHight = randomHight();
        Map *pillar1 = new Map(0,0,pillarHight);        //上下两个柱子
        Map *pillar2 = new Map(0,pillarHight+150,600-(pillarHight+150));
        scene.addItem(pillar1);
        scene.addItem(pillar2);

        allPillars.append(pillar1);      //放入柱子栈，超过一定数量时可销毁对象避免内存泄露
        allPillars.append(pillar2);
    }
    if(!allPillars.isEmpty()){
        Map *p = allPillars.front();
        if(p&&p->pos().x()==80){
            scoreCounter++;
            emit scoreChanged(scoreCounter);          //分数变一次则发送一次信号
        }
    }

    if(allPillars.count()>4){           //场景中出现第三个个柱子时去掉第一个(已经不显示)
        for(int i=0;i<2;i++){
            Map *p = allPillars.front();
            allPillars.pop_front();
            delete p;
        }
    }
    tickCounter = tickCounter > 120 ? 0 : tickCounter+1;

    //
    if(tickCounterFly==0){
        bird->setSpead(-3);
    }else if(tickCounterFly==30){
        bird->setSpead(1);
    }else if(tickCounterFly==50){
        bird->setSpead(3);
    }
    tickCounterFly++;
}

bool Controller::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        keyPressed((QKeyEvent *)event);
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
    scene.clear();
    allPillars.clear();
    timer.stop();
    emit gameIsOver();  //发送游戏结束的信号
}
