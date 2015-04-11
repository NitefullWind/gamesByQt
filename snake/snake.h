#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include <QPainter>


class Snake : public QGraphicsItem
{
public:
    Snake(qreal x=0, qreal y=0, int length=0);
    ~Snake();

    QPointF head;

    enum Direction {Up, Down, Left, Right};
    void setDirection(Direction direction);
    Direction nowDirection() {return moveDirection;}

    QPainterPath shape() const;

    void grow(QPointF p);
    bool eatItself;
private:
    QList<QPointF> body;
    QList<QPointF> growPoint;
    enum {Width=30, Height=30};

    Direction moveDirection;
    bool directionIsChanged;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
protected:
    void advance(int phase);
};

#endif // SNAKE_H
