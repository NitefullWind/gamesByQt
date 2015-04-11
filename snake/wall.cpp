#include "wall.h"
#include <QPainter>

Wall::Wall(qreal x, qreal y, qreal w, qreal h) :
    pos_x(x),
    pos_y(y),
    width(w),
    height(h)
{
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillPath(shape(),Qt::gray);
}

QRectF Wall::boundingRect() const
{
    return QRectF(pos_x, pos_y, width, height);
}

QPainterPath Wall::shape() const
{
    QPainterPath p;
    p.addRect(pos_x, pos_y, width, height);
    return p;
}

Wall::~Wall()
{

}

