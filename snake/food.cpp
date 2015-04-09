#include "food.h"
#include <QPainter>

Food::Food(qreal x, qreal y):
    pos_x(x),
    pos_y(y)
{
    setPos(0,0);
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillPath(shape(),Qt::green);
}

QRectF Food::boundingRect() const
{
    return QRectF(pos_x,pos_y,30,30);
}

QPainterPath Food::shape() const
{
    QPainterPath path;
    path.addRoundedRect(pos_x,pos_y,30,30,15,15,Qt::AbsoluteSize);
    return path;
}

Food::~Food()
{

}

