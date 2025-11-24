#include "red_block.h"
#include "config.h"

red_block::red_block() {

    //加载方块资源
    m_red_block.load(BLOCK_PATH);

    //方块坐标初始化
    m_red_block_X=0;
    m_red_block_Y=0;

    //方块状态(默认闲置）
    m_Free=true;

    //方块状态(默认存活）
    m_Free1=true;

    //方块边框
    m_Rect.setWidth(m_red_block.width()-4);
    m_Rect.setHeight(m_red_block.height()-2);
    m_Rect.moveTo(m_red_block_X+2, m_red_block_Y+1);


}
