#ifndef BIRD_H
#define BIRD_H

#include <QGraphicsItem>

class Bird : public QGraphicsItem
{
public:
    Bird(QGraphicsItem *parent = 0);
    void setHight(const qreal h) {hight = h;}
    void setSpead(const qreal sp) {spead = sp;}
    bool isCollided() {return collide;}
    ~Bird();

private:
    void checkCollisions();
    bool collide;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    qreal hight, spead;
protected:
    void advance(int step);
};

#endif // BIRD_H
