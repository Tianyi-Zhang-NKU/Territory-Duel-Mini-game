#ifndef WINSCENE_H
#define WINSCENE_H

#include <QMainWindow>

class winscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit winscene(QWidget *parent = nullptr);

    //游戏胜利界面背景图片对象
    QPixmap m_winmap;

    //绘制到屏幕中 函数名称不可改
    void paintEvent(QPaintEvent*);


signals:
};

#endif // WINSCENE_H
