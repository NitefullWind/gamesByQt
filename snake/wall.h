#ifndef WALL_H
#define WALL_H

#include <QGraphicsItem>

class Wall : public QGraphicsItem
{
public:
    Wall(qreal x=0,qreal y=0,qreal w=0,qreal h=0);
    ~Wall();
private:
    qreal pos_x, pos_y, width, height;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    QPainterPath shape() const;
};

#endif // WALL_H
