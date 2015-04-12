#include "snake.h"

Snake::Snake(qreal x, qreal y, int length, QString dir, QColor color, QString name):
    head(QPointF(x,y)),
    moveDirection(Right),
    eatItself(false),
    score(0),
    name(name)
{
    body << head;
    if(dir=="right"){
        for(int i=0;i<length;i++){   //添加三次为初始蛇身
            head.rx() += Width;     //头向右移动Width像素
            body << head;           //将蛇头加入蛇身中
        }
    }else if(dir=="left"){
        for(int i=0;i<length;i++){
            head.rx() -= Width;
            body << head;
        }
    }

    bodyColor = color;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setBrush(bodyColor);
    foreach (QPointF p, growPoint) {    //遍历蛇身上吃到食物的点，进行绘画
        if(body.contains(p)){
            painter->drawEllipse(p.rx(), p.ry(), Width, Height);
        }else{
            growPoint.pop_front();
        }
    }
    painter->fillPath(shape(), bodyColor);

    painter->setBrush(Qt::white);
    painter->drawEllipse((head.rx()+10),(head.ry()+10),15,10);
    painter->setBrush(Qt::black);
    painter->drawEllipse((head.rx()+18),(head.ry()+14),2,3);

    painter->drawLine(head.rx()+20,head.ry()+25,head.rx()+30,head.ry()+25);
}

QRectF Snake::boundingRect() const
{
    return QRectF(-300,-400,600,800);
    /************
                       -Height
                     -Width +---+---+
     以元素所在位置为中心    |___|___|
                            |   |   |
                            +---+---+ Width
                                   Height
    **************/
}

QPainterPath Snake::shape() const
{
    QPainterPath path;
    foreach (QPointF p, body) {     //遍历蛇身，画出路径
        path.addRect(p.rx(), p.ry(), Width, Height);
    }
    return path;
}

void Snake::advance(int phase)
{
    if(!phase){
        return;
    }else{
        switch (moveDirection) {
        case Up:
            moveUp();
            break;
        case Down:
            moveDown();
            break;
        case Left:
            moveLeft();
            break;
        case Right:
            moveRight();
            break;
        default:
            break;
        }

        eatItself = (body.indexOf(head) == -1) ? false : true;     //检测是否吃到了自己

        body << head;
        body.pop_front();
        directionIsChanged = true;
    }
}

void Snake::setDirection(Direction direction)
{
    //只有再蛇移动后才接受设置新方向
    if(directionIsChanged){
        moveDirection = direction;
        directionIsChanged = false;
    }
}

void Snake::moveUp()
{
    head.ry() -= Height;
    if(head.ry()<-380){
        head.ry() = 330;
    }
}

void Snake::moveDown()
{
    head.ry() += Height;
    if(head.ry()>330){
        head.ry() = -360;
    }
}

void Snake::moveLeft()
{
    head.rx() -= Width;
    if(head.rx()<-270){
        head.rx() = 240;
    }
}

void Snake::moveRight()
{
    head.rx() += Width;
    if(head.rx()>240){
        head.rx() = -270;
    }
}

void Snake::grow(QPointF p)
{
    body << p;
    growPoint << p;     //用body << p;也能实现移动，但p点在body上时显示不出来。。。
    score++;            //加一分
}

void Snake::beEaten()
{
    body.pop_front();
    score--;
}

Snake::~Snake()
{

}

