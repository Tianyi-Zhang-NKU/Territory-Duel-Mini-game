#include "enemy_plane.h"
#include "config.h"

enemy_plane::enemy_plane() {

    //初始化加载敌机对象
    m_enemy_plane.load(ENEMY_PLANE_PATH);

    //初始化测试敌机坐标
    m_enemy_plane_posX=(GAME_WIDTH - m_enemy_plane.width()) * 0.5;
    m_enemy_plane_posY=4;

    //敌机边框
    m_Rect.setWidth(m_enemy_plane.width()-4);
    m_Rect.setHeight(m_enemy_plane.height()-2);
    m_Rect.moveTo(m_enemy_plane_posX+2,m_enemy_plane_posY+1);

}
