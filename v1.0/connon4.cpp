#include "connon4.h"
#include "config.h"

connon4::connon4() {

    //初始化加载加农炮4对象
    m_connon4.load(CONNON4_PATH);

    //初始化测试加农炮4坐标
    m_connon4_posX=(GAME_WIDTH - m_connon4.width()) * 0.5;
    m_connon4_posY=GAME_HEIGHT - m_connon4.height();

    //加农炮4边框
    m_Rect.setWidth(m_connon4.width()-4);
    m_Rect.setHeight(m_connon4.height()-2);
    m_Rect.moveTo(m_connon4_posX+2,m_connon4_posY+1);

}
