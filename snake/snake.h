#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include <QPainter>


class Snake : public QGraphicsItem
{
public:
    Snake(QGraphicsItem *parent = 0);
    ~Snake();

    enum Direction {Up, Down, Left, Right};
    Direction moveDirection;
    void setDirection(Direction direction);
private:
    QPointF head;
    QList<QPointF> body;
    enum {Width=30, Height=30};

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    QPainterPath shape() const;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
protected:
    void advance(int phase);
};

#endif // SNAKE_H
