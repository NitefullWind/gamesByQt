#include "food.h"
#include <QPainter>

Food::Food(qreal x, qreal y):
    pos_x(x),
    pos_y(y)
{
    setPos(x,y);
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillPath(shape(),Qt::yellow);
}

QRectF Food::boundingRect() const
{
    return QRectF(0,0,30,30);
}

QPainterPath Food::shape() const
{
    QPainterPath path;
    path.addRoundedRect(0,0,30,30,15,15,Qt::AbsoluteSize);
    return path;
}

Food::~Food()
{

}

