#ifndef MYPUSHBOTTON_H
#define MYPUSHBOTTON_H

#include <QPushButton>

class mypushbotton : public QPushButton
{
    Q_OBJECT
public:
    //参数1 正常显示图片路径；参数2 按下后切换图片路径
    mypushbotton(QString normalimg, QString pressimg ="");

    QString normalPath;
    QString pressPath;

    //实现按钮的跳跃
    void zoom1();
    void zoom2();

signals:
};

#endif // MYPUSHBOTTON_H
