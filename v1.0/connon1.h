#ifndef CONNON1_H
#define CONNON1_H
#include <Qpixmap>
#include "bullet.h"
#include "config.h"

class connon1
{
public:
    connon1();

    //发射子弹
    void shoot();

    //设置加农炮1的位置
    void setPosition(int x,int y);

    //加农炮1资源对象
    QPixmap m_connon1;

    //加农炮1坐标
    int m_connon1_posY;
    int m_connon1_posX;

    //加农炮1的矩形边框(用于碰撞检测)
    QRect m_Rect;

    //加农炮1弹匣
    bullet m_bullets [CONNON1_BULLET_NUM];

    //发射间隔记录
    int m_recorder=0;

};

#endif // CONNON1_H
