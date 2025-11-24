#include "mypushbotton.h"
#include "QDebug"
#include <QPropertyAnimation>


mypushbotton::mypushbotton(QString normalimg, QString pressimg)
{
    this->normalPath=normalimg;
    this->pressPath=pressimg;

    //创建QPixmap对象
    QPixmap pix;
    bool ret = pix.load(this->normalPath);
    if(!ret){
        QString str=QString("图标加载失败,失败的路径是:%1!").arg(this->normalPath);
        qDebug() << str;
    }
    //设置按钮固定尺寸
    this->setFixedSize (pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;)");
    //设置图标
    this->setIcon (pix);
    //设置图标大小
    this->setIconSize (QSize(pix.width(),pix.height()));



}

void mypushbotton::zoom1()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "gyeometry");
    //设置动画间隔
    animation->setDuration (1000);
    //设置起始位置
    animation->setStartValue (QRect (this->x(), this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue (QRect (this->x(),this->y()+15,this->width(),this->height()));
    //设置动画曲线
    animation->setEasingCurve (QEasingCurve::OutBounce);
    //执行动画
    animation->start (QAbstractAnimation::DeleteWhenStopped);
}

void mypushbotton::zoom2()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "gyeometry");
    //设置动画间隔
    animation->setDuration (1000);
    //设置起始位置
    animation->setStartValue (QRect (this->x(), this->y()+15,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue (QRect (this->x(),this->y(),this->width(),this->height()));
    //设置动画曲线
    animation->setEasingCurve (QEasingCurve::OutBounce);
    //执行动画
    animation->start (QAbstractAnimation::DeleteWhenStopped);
}
