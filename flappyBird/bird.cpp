#include "bird.h"
#include "controller.h"
#include <QPainter>
#include <QDebug>
#include <QList>

Bird::Bird(QGraphicsItem *parent)
    :QGraphicsItem(parent)
    ,hight(300)
    ,spead(4)
    ,angle(0)
    ,collide(false)
{
    setPos(50,300);
    setZValue(1);
}

QRectF Bird::boundingRect() const
{
    return QRectF(0,0,45,35);
}

QPainterPath Bird::shape() const
{
    QPainterPath path;
    path.addEllipse(0,0,45,35);
    return path;
}

void Bird::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->rotate(angle);
    painter->setRenderHint(QPainter::Antialiasing, true);       //启用反走样
    //body
    painter->setBrush(Qt::blue);
    painter->drawEllipse(0,0,40,30);

    //mouth
    painter->setBrush(Qt::yellow);
    painter->drawRoundedRect(24,15,21,5,3,3);
    painter->drawRoundedRect(24,21,18,5,3,3);
    painter->rotate(45);
    painter->drawRect(30,-6,5,5);
    painter->rotate(-45);

    //eye
    painter->setBrush(Qt::white);
    painter->rotate(10);        //设置画笔旋转
    painter->drawEllipse(23,-3,18,13);
    painter->rotate(-10);
    painter->setBrush(Qt::black);
    painter->drawEllipse(32,7,3,3);

    //wing
    painter->setBrush(Qt::white);
    painter->drawRoundedRect(0,10,20,7,3,3);
}

void Bird::advance(int step)
{
    if(!step){
        return;
    }else{
        hight += spead;
        /*if(spead==-3){
            angle = -15;
        }else if(spead==1){
            angle = 0;
        }else{
            angle = 15;
        }*/
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

