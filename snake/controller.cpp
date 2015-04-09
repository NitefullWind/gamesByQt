#include "controller.h"

Controller::Controller(QGraphicsScene &scene, QObject *parent):
    QObject(parent),
    scene(scene)
{
    newGame();
    scene.installEventFilter(this);                                 //安装事件过滤器
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));    //连接计时器与scene的advance函数
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(update()));     //调用update()，这样元素重绘后才会刷新界面
}

void Controller::drawWall()
{
    //初始化四周的墙
    wall[0] = new Wall(-300,-400,600,30);
    wall[1] = new Wall(-300,-400,30,800);
    wall[2] = new Wall(-300,370,600,30);
    wall[3] = new Wall(270,-400,30,800);

    //添加到场景中
    for(int i=0;i<4;i++){
        scene.addItem(wall[i]);
    }
}

void Controller::drawSnake()
{
    snake = new Snake();
    scene.addItem(snake);
}

void Controller::drawFood()
{
    food = new Food(0,0);
    scene.addItem(food);
}

void Controller::newGame()
{
    drawWall();
    drawSnake();
    drawFood();

    gameIsPause = true;
    pause();
}

void Controller::pause()
{
    //游戏暂停中则开始计时，否则停止计时
    if(gameIsPause){
        timer.start(1000/3);
    }else{
        timer.stop();
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
    if(event->key() == Qt::Key_Up){
        snake->setDirection(Snake::Up);
    }else if(event->key() == Qt::Key_Down){
        snake->setDirection(Snake::Down);
    }else if(event->key() == Qt::Key_Left){
        snake->setDirection(Snake::Left);
    }else if(event->key() == Qt::Key_Right){
        snake->setDirection(Snake::Right);
    }
}


Controller::~Controller()
{

}

