#ifndef CONNON3_H
#define CONNON3_H
#include <Qpixmap>
#include "bullet.h"
#include "config.h"

class connon3
{
public:
    connon3();

    //发射子弹
    void shoot();

    //设置加农炮3的位置
    void setPosition(int x,int y);

    //加农炮3资源对象
    QPixmap m_connon3;

    //加农炮3坐标
    int m_connon3_posY;
    int m_connon3_posX;

    //加农炮3的矩形边框(用于碰撞检测)
    QRect m_Rect;

    //加农炮3弹匣左前
    bullet m_bullets_1 [CONNON3_BULLET_NUM_1];

    //加农炮3弹匣正前
    bullet m_bullets_2 [CONNON3_BULLET_NUM_2];

    //加农炮3弹匣右前
    bullet m_bullets_3 [CONNON3_BULLET_NUM_3];

    //发射间隔记录
    int m_recorder=0;

    // 冷却状态
    void startCooling();
    void updateCooling();
    bool isCooling() const { return m_cooling; }
    float m_cooldownOpacity = 1.0f;

private:
    bool m_cooling = false;
    int m_coolingTime = 0;

};

#endif // CONNON3_H
