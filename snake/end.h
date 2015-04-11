#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <QGraphicsItem>

class End : public QGraphicsItem
{
public:
    End(qreal score = 0, qreal best = 0);
    ~End();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    qreal newScore, highestMark;
};

#endif // GAMEOVER_H
