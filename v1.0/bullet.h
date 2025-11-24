#ifndef BULLET_H
#define BULLET_H
#include <Qpixmap>

class bullet
{
public:
    bullet();

    //更新子弹坐标
    void updatePosition();

public:
    //子弹资源对象
    QPixmap m_bullet;

    //子弹坐标
    int m_bullet_X;
    int m_bullet_Y;

    //子弹是否闲置
    bool m_Free;

    //设置子弹的类型
    int m_bullet_type;

    //子弹的矩形边框(用于碰撞检测)
    QRect m_Rect;

};

#endif // BULLET_H
