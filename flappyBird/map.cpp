#include "map.h"
#include <QPainter>

Map::Map(qreal x, qreal y, qreal hight):
    rectX(0),
    rectY(0),
    rectHight(0)

{
    rectHight = 0;
    rectPos = WindowWidth;
    rectX = x;
    rectY = y;
    rectHight = hight;
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillPath(shape(),Qt::green);
    painter->restore();
}

QRectF Map::boundingRect() const
{
    return QRectF(rectX,rectY,RectWidth,rectHight);
}

QPainterPath Map::shape() const
{
    QPainterPath p;
    p.addRect(rectX,rectY,RectWidth,rectHight);
    return p;
}

void Map::advance(int step)
{
    if(!step){
        return;
    }else{
        rectPos -= 2;
    }
    setPos(rectPos,0);      //设置元素坐标
}

Map::~Map()
{
}
