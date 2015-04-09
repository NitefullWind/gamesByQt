#include "snake.h"
#include <QDebug>

Snake::Snake(QGraphicsItem *parent):
    QGraphicsItem(parent),
    head(QPointF(-120,0)),
    moveDirection(Right)
{
    for(int i=0;i<4;i++){   //添加四次为初始蛇身
        body << head;           //将蛇头加入蛇身中
        head.rx() += Width;     //头向右移动Width像素
    }
    setPos(0,0);
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillPath(shape(), Qt::yellow);
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
        qDebug() << p.rx() ;
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
        body << head;
        body.pop_front();
        if(head.rx()>230){
            head.rx() = -300;
        }
    }
}

void Snake::setDirection(Direction direction)
{
    moveDirection = direction;
}

void Snake::moveUp()
{
    head.ry() -= Height;
}

void Snake::moveDown()
{
    head.ry() += Height;
}

void Snake::moveLeft()
{
    head.rx() -= Width;
}

void Snake::moveRight()
{
    head.rx() += Width;
}

Snake::~Snake()
{

}

