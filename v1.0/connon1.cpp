#include "connon1.h"
#include "config.h"

connon1::connon1() {

    //初始化加载加农炮1对象
    m_connon1.load(CONNON1_PATH);

    //初始化测试加农炮1坐标
    m_connon1_posX=(GAME_WIDTH - m_connon1.width()) * 0.5;
    m_connon1_posY=GAME_HEIGHT - m_connon1.height();

    //加农炮1边框
    m_Rect.setWidth(m_connon1.width()-4);
    m_Rect.setHeight(m_connon1.height()-2);
    m_Rect.moveTo(m_connon1_posX+2,m_connon1_posY+1);

}

void connon1::shoot()
{
    //累加时间间隔记录变量
    m_recorder++;

    //如果记录的数字,未达到发射子弹时间间隔,直接return,不发射子弹
    if(m_recorder < BULLET_INTERVAL){
        return;
    }

    //达到发射时间
    m_recorder = 0;

    //发射子弹
    for(int i=0;i<CONNON1_BULLET_NUM;i++){
        //如果是空闲的子弹,进行发射
        if (m_bullets[i].m_Free){

            //将空闲状态改为假
            m_bullets[i].m_Free=false;

            //设置子弹类型
            m_bullets[i].m_bullet_type=2;

            //设置子弹坐标
            m_bullets[i].m_bullet_X = m_connon1_posX+45;
            m_bullets[i].m_bullet_Y = m_connon1_posY;
            break;
        }
    }
    return;
}

void connon1::setPosition(int x, int y)
{
    m_connon1_posX=x;
    m_connon1_posY=y;
    m_Rect.moveTo(m_connon1_posX,m_connon1_posY);
    return;
}
