#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <QGraphicsItem>

class End : public QGraphicsItem
{
public:
    End();
    ~End();
    void setScore(qreal score0, qreal score1);
    void setWinner(QString w);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    QString winner;
    qreal score0, score1;
};

#endif // GAMEOVER_H
