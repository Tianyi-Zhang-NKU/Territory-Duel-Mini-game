#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>
#include "mainscene.h"

class startscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit startscene(QWidget *parent = nullptr);

    //开始界面背景图片对象
    QPixmap m_startmap;

    //绘制到屏幕中 函数名称不可改
    void paintEvent(QPaintEvent*);

    //初始化一个主场景，用于后续的跳转界面
    MainScene * mainscene;


signals:
};

#endif // STARTSCENE_H
