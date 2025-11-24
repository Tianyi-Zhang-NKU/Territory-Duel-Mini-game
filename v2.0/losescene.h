#ifndef LOSESCENE_H
#define LOSESCENE_H

#include <QMainWindow>


class losescene : public QMainWindow
{
    Q_OBJECT
public:
    explicit losescene(QWidget *parent = nullptr);

    //游戏失败界面背景图片对象
    QPixmap m_losemap;

    //绘制到屏幕中 函数名称不可改
    void paintEvent(QPaintEvent*);


signals:
};

#endif // LOSESCENE_H
