#include "connon3.h"
#include "config.h"

connon3::connon3() {

    //初始化加载加农炮3对象
    m_connon3.load(CONNON3_PATH);

    //初始化测试加农炮3坐标(无效坐标)
    m_connon3_posX=-100;
        //90+2;
    m_connon3_posY=-100;
        //GAME_HEIGHT - m_connon3.height()+3;

    //加农炮3边框
    m_Rect.setWidth(m_connon3.width()-4);
    m_Rect.setHeight(m_connon3.height()-2);
    m_Rect.moveTo(m_connon3_posX+2,m_connon3_posY+1);

}
void connon3::shoot()
{
    //累加时间间隔记录变量
    m_recorder++;

    //如果记录的数字,未达到发射子弹时间间隔,直接return,不发射子弹
    if(m_recorder < BULLET_INTERVAL){
        return;
    }

    //达到发射时间
    m_recorder = 0;

    //发射左前子弹
    for(int i=0;i<CONNON3_BULLET_NUM_1;i++){
        //如果是空闲的子弹,进行发射
        if (m_bullets_1[i].m_Free){

            //将空闲状态改为假
            m_bullets_1[i].m_Free = false;

            //设置子弹类型
            m_bullets_1[i].m_bullet_type=1;

            //设置子弹坐标
            m_bullets_1[i].m_bullet_X = m_connon3_posX-30;
            m_bullets_1[i].m_bullet_Y = m_connon3_posY-30;
            break;
        }
    }

    //发射正前子弹
    for(int i=0;i<CONNON3_BULLET_NUM_2;i++){
        //如果是空闲的子弹,进行发射
        if (m_bullets_2[i].m_Free){

            //将空闲状态改为假
            m_bullets_2[i].m_Free = false;

            //设置子弹类型
            m_bullets_2[i].m_bullet_type=2;

            //设置子弹坐标
            m_bullets_2[i].m_bullet_X = m_connon3_posX+30;
            m_bullets_2[i].m_bullet_Y = m_connon3_posY-30;
            break;
        }
    }

    //发射右前子弹
    for(int i=0;i<CONNON3_BULLET_NUM_3;i++){
        //如果是空闲的子弹,进行发射
        if (m_bullets_3[i].m_Free){

            //将空闲状态改为假
            m_bullets_3[i].m_Free = false;

            //设置子弹类型
            m_bullets_3[i].m_bullet_type=3;

            //设置子弹坐标
            m_bullets_3[i].m_bullet_X = m_connon3_posX+90;
            m_bullets_3[i].m_bullet_Y = m_connon3_posY-30;
            break;
        }
    }
    return;
}

void connon3::setPosition(int x, int y)
{
    m_connon3_posX=x;
    m_connon3_posY=y;
    m_Rect.moveTo(m_connon3_posX,m_connon3_posY);
    return;
}



void connon3::startCooling() {
    m_cooling = true;
    m_coolingTime = 0;
}

void connon3::updateCooling() {
    if (!m_cooling) return;
    m_coolingTime += GAME_RATE;
    m_cooldownOpacity = 1.0f - static_cast<float>(m_coolingTime) / CONNON3_COOLDOWN;
    if (m_cooldownOpacity < 0.0f) m_cooldownOpacity = 0.0f;
    if (m_coolingTime >= CONNON3_COOLDOWN) {
        m_cooling = false;
        m_coolingTime = 0;
        m_cooldownOpacity = 0.0f;
    }
}

