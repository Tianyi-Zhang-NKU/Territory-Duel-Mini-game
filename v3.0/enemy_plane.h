#ifndef ENEMY_PLANE_H
#define ENEMY_PLANE_H
#include <Qpixmap>

class enemy_plane
{
public:
    enemy_plane();

    //更新敌机坐标
    void updatePosition();

    //设置敌机的位置
    void setPosition(int x,int y);

    //敌机资源对象
    QPixmap m_enemy_plane;

    //敌机坐标
    int m_enemy_plane_posY;
    int m_enemy_plane_posX;

    //敌机的矩形边框(用于碰撞检测)
    QRect m_Rect;



};

#endif // ENEMY_PLANE_H
