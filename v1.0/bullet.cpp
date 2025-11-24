#include "bullet.h"
#include "config.h"

bullet::bullet() {

    //加载子弹资源
    m_bullet.load(BULLET_PATH);

    //子弹坐标初始化
    m_bullet_X=0;
    m_bullet_Y=0;

    //子弹状态(默认闲置）
    m_Free=true;

    //初始化子弹的类型
    //1为左前；2为默认正前；3为右前
    m_bullet_type=2;

    //子弹边框
    m_Rect.setWidth(m_bullet.width()-4);
    m_Rect.setHeight(m_bullet.height()-2);
    m_Rect.moveTo(m_bullet_X+2,m_bullet_Y+1);

}

//更新子弹坐标函数
void bullet::updatePosition()
{
    //空闲状态下的子弹,不需要计算坐标
    if(m_Free){
        return;
    }

    //左前子弹向左上方移动
    if(m_bullet_type==1){
        //子弹从上方超出屏幕,重新变为空闲状态
        if(m_bullet_Y<= - m_Rect.height()){
            m_Free=true;
            return;
        }
        //子弹位置从左侧超出屏幕,反弹
        if((m_bullet_Y > - m_Rect.height())&&(m_bullet_X < 10)){
            m_bullet_X += GAME_V;
            m_bullet_Y -= GAME_V;
            m_Rect.moveTo(m_bullet_X+2, m_bullet_Y+1);
            m_bullet_type=3;
            return;
        }
        m_bullet_X -= GAME_V;
        m_bullet_Y -= GAME_V;
        m_Rect.moveTo(m_bullet_X+2, m_bullet_Y+1);
        return;
    }

    //正前子弹向上移动
    if(m_bullet_type==2){
        //子弹从上方位置超出屏幕,重新变为空闲状态
        if(m_bullet_Y<= - m_Rect.height()){
            m_Free=true;
            return;
        }
        m_bullet_Y -= GAME_V;
        m_Rect.moveTo(m_bullet_X+2, m_bullet_Y+1);
        return;
    }

    //右前子弹向右上方移动
    if(m_bullet_type==3){
        //子弹位从上方超出屏幕,重新变为空闲状态
        if(m_bullet_Y<= - m_Rect.height()){
            m_Free=true;
            return;
        }
        //子弹位置从右侧超出屏幕,反弹
        if((m_bullet_Y > - m_Rect.height())&&(m_bullet_X > GAME_WIDTH-40)){
            m_bullet_X -= GAME_V;
            m_bullet_Y -= GAME_V;
            m_Rect.moveTo(m_bullet_X+2, m_bullet_Y+1);
            m_bullet_type=1;
            return;
        }
        m_bullet_X += GAME_V;
        m_bullet_Y -= GAME_V;
        m_Rect.moveTo(m_bullet_X+2, m_bullet_Y+1);
        return;
    }
    return;
}
