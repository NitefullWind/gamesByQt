#ifndef MAP_H
#define MAP_H

#include <QGraphicsItem>

class Map : public QGraphicsItem
{
public:
    Map(qreal x, qreal y, qreal hight);
    ~Map();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    enum {RectWidth=50,WindowWidth=400,WindowHight=600};
    qreal rectX, rectY, rectHight, rectPos;

protected:
    void advance(int step);
};

#endif // MAP_H
