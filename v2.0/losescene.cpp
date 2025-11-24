#include "losescene.h"
#include "config.h"
#include "mypushbotton.h"
#include <QIcon>
#include <QPainter>
#include <QDebug>

losescene::losescene(QWidget *parent)
    : QMainWindow{parent}
{
    //初始化加载地图对象
    m_losemap.load(LOSE_MAP_PATH);

    //设置窗口固定尺寸
    setFixedSize (GAME_WIDTH_1,GAME_HEIGHT);

    //设置标题
    setWindowTitle ("游戏失败");

    //设置图标
    setWindowIcon(QIcon(":/pictures/00-icon.png"));

    mypushbotton * closeBtn=new mypushbotton(":/pictures/999-closebutton.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()*0.5 - closeBtn->width() *0.5, this->height() *0.55);
    connect(closeBtn, &mypushbotton::clicked, [=] (){
        qDebug()<<"退出游戏";
        closeBtn->zoom1();//向下跳跃
        closeBtn->zoom2();//向上跳跃
        this->close();
    });

}
//绘制屏幕
void losescene::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //this指针，表示画到当前屏幕

    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),m_losemap);
}
