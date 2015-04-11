#include "controller.h"
#include <QDebug>

Controller::Controller(QGraphicsScene &scene, QObject *parent):
    QObject(parent),
    scene(scene),
    score(0),
    food(new Food(0,0))
{
    newGame();
    scene.installEventFilter(this);                                 //安装事件过滤器
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));    //连接计时器与scene的advance函数
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(update()));     //调用update()，这样元素重绘后才会刷新界面
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkCollisions())); //检测碰撞
}

void Controller::drawWall()
{
    //初始化四周的墙
    wall[0] = new Wall(-300,-390,600,30);
    wall[1] = new Wall(-300,-390,30,780);
    wall[2] = new Wall(-300,360,600,30);
    wall[3] = new Wall(270,-390,30,780);

    //添加到场景中
    for(int i=0;i<4;i++){
        scene.addItem(wall[i]);
    }
}

void Controller::drawSnake()
{
    snake = new Snake(-120,0,4);
    scene.addItem(snake);
}

void Controller::drawFood()
{
    qreal x=0, y=0;
    do{                                                 //随机产生食物坐标
        x = (qrand() % 18)*30-270;
        y = (qrand() % 24)*30-360;
    }while(snake->shape().contains(QPointF(x,y))||food->x()==x&&food->y()==y);      //检测食物的坐标是否在蛇身上
    food = new Food(x,y);
    scene.addItem(food);
}

void Controller::newGame()
{
    drawWall();
    drawSnake();
    drawFood();

    gameIsPause = false;
    pause();
}

void Controller::pause()
{
    //游戏暂停中则开始计时，否则停止计时
    if(gameIsPause){
        timer.start(1000/3);
        gameIsPause = false;
    }else{
        timer.stop();
        gameIsPause = true;
    }
}

bool Controller::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        keyPress((QKeyEvent *) event);  //QEvent强制转换为QKeyEvent类型，传递给keyPress函数
        return true;
    }else{
        return QObject::eventFilter(object,event);  //否则传给QObject的事件过滤器
    }
}

void Controller::keyPress(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        if(snake->nowDirection()!=Snake::Down)
            snake->setDirection(Snake::Up);
        break;
    case Qt::Key_Down:
        if(snake->nowDirection()!=Snake::Up)
            snake->setDirection(Snake::Down);
        break;
    case Qt::Key_Left:
        if(snake->nowDirection()!=Snake::Right)
            snake->setDirection(Snake::Left);
        break;
    case Qt::Key_Right:
        if(snake->nowDirection()!=Snake::Left)
            snake->setDirection(Snake::Right);
        break;
    case Qt::Key_Space:
        pause();
        break;
    default:
        break;
    }
}

void Controller::checkCollisions()
{
    if(snake->shape().contains(food->pos())){
        eatFood();
    }
    if(snake->eatItself){
        gameIsOver(true);
    }
}

void Controller::gameIsOver(bool isOk)
{
    if(isOk){
        end = new End(score);
        scene.addItem(end);
        pause();
        //scene.clear();
        //newGame();
    }
}

void Controller::eatFood()
{
    snake->grow(food->pos());
    scene.removeItem(food);
    drawFood();
    score++;
}

Controller::~Controller()
{

}

