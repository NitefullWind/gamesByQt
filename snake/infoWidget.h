#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <QGraphicsItem>

class InfoWidget : public QGraphicsItem
{
public:
    InfoWidget();
    ~InfoWidget();
    void setScore(qreal score0, qreal score1);
    void setInformation(QString w);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    QString information;
    qreal score0, score1;
};

#endif // GAMEOVER_H
