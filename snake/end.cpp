#include "end.h"
#include <QPainter>

End::End():
    score0(0),
    score1(0),
    winner("")
{
}

void End::setScore(qreal score0, qreal score1)
{
    this->score0 = score0;
    this->score1 = score1;
    update(boundingRect());
}

void End::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::lightGray);
    painter->drawRect(-300,-500,600,100);

    QRectF snake0(-300,-500,200,100);
    QFont font("微软雅黑",15);
    painter->setFont(font);
    painter->setPen(Qt::red);
    painter->drawText(snake0,"Red Snake:\n Score : " + QString::number(score0), QTextOption(Qt::AlignCenter));

    QRectF snake1(100,-500,200,100);
    painter->setFont(font);
    painter->setPen(Qt::green);
    painter->drawText(snake1,"Green Snake:\n Score : " + QString::number(score1), QTextOption(Qt::AlignCenter));

    QRectF winnerRect(-100,-500,200,100);
    QFont font1("微软雅黑",20,QFont::Bold,true);     //设置字体样式：类型，大小，加粗，斜体
    painter->setFont(font1);         //添加字体
    painter->setPen(Qt::yellow);
    painter->drawText(winnerRect,winner,QTextOption(Qt::AlignCenter));
}

QRectF End::boundingRect() const
{
    return QRectF(-300,-450,600,50);
}

void End::setWinner(QString w)
{
    winner = w;
    update(boundingRect());
}

End::~End()
{

}
