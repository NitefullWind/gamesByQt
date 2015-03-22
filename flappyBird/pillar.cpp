#include "pillar.h"
#include <QPainter>

Pillar::Pillar(qreal x, qreal y, qreal hight):
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

void Pillar::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->save();
    painter->fillPath(shape(),Qt::green);
    painter->restore();
}

QRectF Pillar::boundingRect() const
{
    return QRectF(rectX,rectY,RectWidth,rectHight);
}

QPainterPath Pillar::shape() const
{
    QPainterPath p;
    p.addRect(rectX,rectY,RectWidth,rectHight);
    return p;
}

void Pillar::advance(int step)
{
    if(!step){
        return;
    }else{
        rectPos -= 2;
    }
    setPos(rectPos,0);      //设置元素坐标
}

Pillar::~Pillar()
{
}
