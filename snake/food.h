#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsItem>

class Food : public QGraphicsItem
{
public:
    Food(qreal x=0, qreal y=0);
    ~Food();

    QPainterPath shape() const;
private:
    qreal pos_x, pos_y;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
};

#endif // FOOD_H
