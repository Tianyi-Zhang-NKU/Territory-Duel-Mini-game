#include "connon1.h"
#include "config.h"


connon1::connon1() {

    //初始化加载加农炮1对象
    m_connon1.load(CONNON1_PATH);

    //初始化测试加农炮1坐标（无效值）
    m_connon1_posX=-100;
    m_connon1_posY=-100;

    //加农炮1边框
    m_Rect.setWidth(m_connon1.width()-4);
    m_Rect.setHeight(m_connon1.height()-2);
    m_Rect.moveTo(m_connon1_posX+2,m_connon1_posY+1);

}

void connon1::shoot()
{
    //if(m_cooling) return; // 冷却中不射击

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
            m_bullets[i].m_bullet_X = m_connon1_posX+30;
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

void connon1::startCooling()
{
    m_cooling = true;
    m_coolingTime = 0;
}

void connon1::updateCooling()
{
    if (!m_cooling) return;

    m_coolingTime += GAME_RATE;

    // 计算当前灰度遮罩的透明度，随时间线性下降
    m_cooldownOpacity = 1.0f - static_cast<float>(m_coolingTime) / CONNON1_COOLDOWN;
    if (m_cooldownOpacity < 0.0f) m_cooldownOpacity = 0.0f;

    if (m_coolingTime >= CONNON1_COOLDOWN) {
        m_cooling = false;
        m_coolingTime = 0;
        m_cooldownOpacity = 0.0f;
    }
}

