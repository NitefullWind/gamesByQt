#include "bird.h"
#include "controller.h"
#include <QPainter>
#include <QDebug>
#include <QList>

Bird::Bird(QGraphicsItem *parent)
    :QGraphicsItem(parent)
    ,hight(300)
    ,spead(3)
    ,collide(false)
{
    setPos(50,300);
    setZValue(1);
}

QRectF Bird::boundingRect() const
{
    return QRectF(0,0,40,30);
}

QPainterPath Bird::shape() const
{
    QPainterPath path;
    path.addEllipse(0,0,40,30);
    return path;
}

void Bird::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillPath(shape(),Qt::red);
}

void Bird::advance(int step)
{
    if(!step){
        return;
    }else{
        hight += spead;
    }
    setPos(50,hight);
    checkCollisions();
}

void Bird::checkCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    if(collisions.count()>0 || hight<=0 || hight>=570){
        collide = true;
    }
}

Bird::~Bird()
{

}

