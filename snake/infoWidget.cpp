#include "infoWidget.h"
#include "constants.h"
#include <QPainter>

InfoWidget::InfoWidget():
    score0(0),
    score1(0),
    information("")
{
    setPos(-SceneX-Width,-PosY);
}

void InfoWidget::setScore(qreal score0, qreal score1)
{
    this->score0 = score0;
    this->score1 = score1;
    update(boundingRect());
}

void InfoWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::lightGray);
    painter->drawRect(0,0,150,SceneHeight);

    QRectF snake0(0,0,150,200);
    QFont font("微软雅黑",15);
    painter->setFont(font);
    painter->setPen(Qt::red);
    painter->drawText(snake0,"红蛇:\n 得分 : " + QString::number(score0), QTextOption(Qt::AlignCenter));

    QRectF snake1(0,400,150,200);
    painter->setFont(font);
    painter->setPen(Qt::green);
    painter->drawText(snake1,"率蛇:\n 得分 : " + QString::number(score1), QTextOption(Qt::AlignCenter));

    QRectF informationRect(0,200,150,200);
    QFont font1("微软雅黑",20,QFont::Bold,true);     //设置字体样式：类型，大小，加粗，斜体
    painter->setFont(font1);         //添加字体
    painter->setPen(Qt::black);
    painter->drawText(informationRect,information,QTextOption(Qt::AlignCenter));
}

QRectF InfoWidget::boundingRect() const
{
    return QRectF(0,0,150,SceneHeight);
}

void InfoWidget::setInformation(QString w)
{
    information = w;
    update(boundingRect());
}

InfoWidget::~InfoWidget()
{

}
