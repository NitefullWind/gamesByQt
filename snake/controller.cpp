#include "controller.h"

Controller::Controller(QGraphicsScene &scene, QObject *parent):
    QObject(parent),
    scene(scene),
    food(new Food(0,0)),
    gameIsOver(false)
{
    drawWall();
    drawSnake();
    drawFood();
    end = new End();
    scene.addItem(end);

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
    snake[0] = new Snake(-270,-360,3,"right",Qt::red,"Red Snake");
    scene.addItem(snake[0]);
    snake[1] = new Snake(240,330,3,"left",Qt::green,"Green Snake");
    snake[1]->setDirection(Snake::Left);
    scene.addItem(snake[1]);
}

void Controller::drawFood()
{
    if(!food){
        scene.removeItem(food);
    }
    qreal x=0, y=0;
    do{                                                 //随机产生食物坐标
        x = (qrand() % 18)*30-270;
        y = (qrand() % 24)*30-360;
    }while(snake[0]->shape().contains(QPointF(x,y))||snake[1]->shape().contains(QPointF(x,y))||food->x()==x&&food->y()==y);      //检测食物的坐标是否在蛇身上
    food = new Food(x,y);
    scene.addItem(food);
}

void Controller::newGame()
{
    scene.removeItem(snake[0]);
    scene.removeItem(snake[1]);
    scene.removeItem(food);

    drawSnake();
    drawFood();

    end->setScore(snake[0]->getScore(), snake[1]->getScore());

    gameIsOver = false;
    gameIsPause = false;
    pause();
}

void Controller::pause()
{
    if(!gameIsOver){
        //游戏暂停中则开始计时，否则停止计时
        if(gameIsPause){
            timer.start(1000/3);
            gameIsPause = false;
            end->setWinner("快跑啊，游戏开始啦~");
        }else{
            timer.stop();
            gameIsPause = true;
            end->setWinner("兄弟们歇会吧,游戏暂停ing.");
        }
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
        if(snake[0]->nowDirection()!=Snake::Down)
            snake[0]->setDirection(Snake::Up);
        break;
    case Qt::Key_Down:
        if(snake[0]->nowDirection()!=Snake::Up)
            snake[0]->setDirection(Snake::Down);
        break;
    case Qt::Key_Left:
        if(snake[0]->nowDirection()!=Snake::Right)
            snake[0]->setDirection(Snake::Left);
        break;
    case Qt::Key_Right:
        if(snake[0]->nowDirection()!=Snake::Left)
            snake[0]->setDirection(Snake::Right);
        break;
    case Qt::Key_W:
        if(snake[1]->nowDirection()!=Snake::Down)
            snake[1]->setDirection(Snake::Up);
        break;
    case Qt::Key_S:
        if(snake[1]->nowDirection()!=Snake::Up)
            snake[1]->setDirection(Snake::Down);
        break;
    case Qt::Key_A:
        if(snake[1]->nowDirection()!=Snake::Right)
            snake[1]->setDirection(Snake::Left);
        break;
    case Qt::Key_D:
        if(snake[1]->nowDirection()!=Snake::Left)
            snake[1]->setDirection(Snake::Right);
        break;
    case Qt::Key_Space:
        pause();
        break;
    case Qt::Key_Escape:
        newGame();
        break;
    default:
        break;
    }
}

void Controller::checkCollisions()
{
    if(snake[0]->shape().contains(food->pos())){
        snake[0]->grow(food->pos());
        scene.removeItem(food);
        end->setWinner(snake[0]->getName()+"吃了食物");
        drawFood();
    }else if(snake[1]->shape().contains(food->pos())){
        snake[1]->grow(food->pos());
        scene.removeItem(food);
        end->setWinner(snake[1]->getName()+"吃了食物");
        drawFood();
    }
    if(snake[0]->eatItself){
        gameOver(snake[0]->getName()+"\n把自己给咬了,233333");
    }
    if(snake[1]->eatItself){
        gameOver(snake[1]->getName()+"\n咬自己真的不疼吗 = =！ ");
    }

    //检测两条蛇的碰撞
    if(snake[0]->shape().contains(snake[1]->getHead())){
        if(snake[1]->getHead()==snake[0]->getTail()){       //snake[0]被吃
            snake[1]->grow(snake[1]->getHead());
            snake[0]->beEaten();
            end->setWinner(snake[1]->getName()+"咬了"+snake[0]->getName());
        }else{          //没吃到尾巴则snake[0]撞死
            gameOver(snake[1]->getName()+"兄弟,只能咬人家尾巴好不好...");
        }
    }
    if(snake[1]->shape().contains(snake[0]->getHead())){
        if(snake[0]->getHead()==snake[1]->getTail()){       //snake[1]被吃
            snake[0]->grow(snake[0]->getHead());
            snake[1]->beEaten();
            end->setWinner(snake[0]->getName()+"咬了"+snake[1]->getName());
        }else{
            gameOver("嘿，"+snake[0]->getName()+"\n去咬他的尾巴啊！！！");
        }
    }

    end->setScore(snake[0]->getScore(), snake[1]->getScore());
}

void Controller::gameOver(QString winner)
{
    pause();
    gameIsOver = true;
    end->setWinner(winner);
}

Controller::~Controller()
{

}

