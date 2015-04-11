#include "end.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

End::End(qreal score, qreal best)
{
    setPos(0,0);
    newScore = score;
    highestMark = best;
}

void End::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::lightGray);
    painter->drawRoundRect(-100,-100,200,200,20);

    QRectF rect1(-80,-80,160,60);
    QFont font1("微软雅黑",20,QFont::Bold,true);     //设置字体样式：类型，大小，加粗，斜体
    painter->setFont(font1);         //添加字体
    painter->setPen(Qt::yellow);
    painter->drawText(rect1,"Game Over",QTextOption(Qt::AlignCenter));

    QRectF rect2(-80,-20,160,30);
    QFont font2("微软雅黑",15);
    painter->setFont(font2);
    painter->setPen(Qt::red);
    painter->drawText(rect2,"Score : "+QString::number(newScore), QTextOption(Qt::AlignCenter));

    QRectF rect3(-80,10,160,30);
    painter->drawText(rect3,"Best : "+QString::number(highestMark), QTextOption(Qt::AlignCenter));

    painter->setBrush(Qt::blue);
    painter->drawRoundedRect(-60,40,120,40,10,10);
}

QPainterPath End::shape() const
{
    QPainterPath path;
    path.addRoundRect(-100,-100,200,200,20);
    return path;
}

QRectF End::boundingRect() const
{
    return QRectF(-100,-100,200,200);
}

End::~End()
{

}

