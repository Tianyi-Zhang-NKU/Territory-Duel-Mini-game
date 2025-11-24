#include "winscene.h"
#include "config.h"
#include "mypushbotton.h"
#include <QIcon>
#include <QPainter>
#include <QDebug>

winscene::winscene(QWidget *parent)
    : QMainWindow{parent}
{
    //初始化加载地图对象
    m_winmap.load(WIN_MAP_PATH);

    //设置窗口固定尺寸
    setFixedSize (GAME_WIDTH_1,GAME_HEIGHT);

    //设置标题
    setWindowTitle ("游戏胜利");

    //设置图标
    setWindowIcon(QIcon(":/pictures/00-icon.png"));

    /*气死我了，不让递归，不删这段了留个念想......
    mypushbotton * startBtn=new mypushbotton(":/pictures/999-againbutton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width() *0.5, this->height() *0.75);
    connect(startBtn, &mypushbotton::clicked, [=] (){
        qDebug()<<"再次进入游戏场景";
        startBtn->zoom1();//向下跳跃
        startBtn->zoom2();//向上跳跃
        this->m_startscene->show();
        this->hide();
    });
*/


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
void winscene::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //this指针，表示画到当前屏幕

    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),m_winmap);
}
