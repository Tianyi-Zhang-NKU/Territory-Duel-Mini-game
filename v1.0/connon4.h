#ifndef CONNON4_H
#define CONNON4_H
#include <Qpixmap>

class connon4
{
public:
    connon4();

    //发射子弹
    void shoot();

    //设置加农炮4的位置
    void setPosition(int x,int y);

    //加农炮4资源对象
    QPixmap m_connon4;

    //加农炮4坐标
    int m_connon4_posY;
    int m_connon4_posX;

    //加农炮4的矩形边框(用于碰撞检测)
    QRect m_Rect;

};

#endif // CONNON4_H
