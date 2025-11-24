#include "startscene.h"
#include "config.h"
#include "mypushbotton.h"
#include "mainscene.h"
#include <QIcon>
#include <QPainter>
#include <QDebug>

startscene::startscene(QWidget *parent)
    : QMainWindow{parent}
{

    //初始化加载地图对象
    m_startmap.load(START_MAP_PATH);

    //设置窗口固定尺寸
    setFixedSize (GAME_WIDTH_1,GAME_HEIGHT);

    //设置标题
    setWindowTitle (GAME_TITLE);

    //设置图标
    setWindowIcon(QIcon(":/pictures/00-icon.png"));

    this->mainscene =new MainScene;

    mypushbotton * startBtn=new mypushbotton(":/pictures/000-startbutton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width() *0.5, this->height() *0.7);
    connect(startBtn, &mypushbotton::clicked, [=] (){
        qDebug()<<"进入游戏场景";
        startBtn->zoom1();//向下跳跃
        startBtn->zoom2();//向上跳跃
        this->mainscene->show();
        this->mainscene->m_start=true;
        this->hide();
    });
}
//绘制屏幕
void startscene::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //this指针，表示画到当前屏幕

    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),m_startmap);
}
