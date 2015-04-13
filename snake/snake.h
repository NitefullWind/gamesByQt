#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include <QPainter>
#include <QColor>

#include "constants.h"

class Snake : public QGraphicsItem
{
public:
    Snake(qreal x=0, qreal y=0, int length=0, Direction dir=Right, QColor color=Qt::green, QString name="None");
    ~Snake();

    QPointF getHead() {return head;}
    QPointF getTail() {return body.front();}

    void setDirection(Direction direction);
    Direction nowDirection() {return moveDirection;}

    QPainterPath shape() const;

    void grow(QPointF p);
    void beEaten();
    bool eatItself;

    qreal getScore() {return score;}
    QString getName(){return name;}
private:
    QPointF head;
    QList<QPointF> body;
    QList<QPointF> growPoint;
    QColor bodyColor;
    QString name;

    qreal score;

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
