#include "dred_block.h"
#include "config.h"

dred_block::dred_block() {

    //加载方块资源
    m_dred_block.load(DBLOCK_PATH);

    //方块坐标初始化
    m_dred_block_X=0;
    m_dred_block_Y=00;

    //方块状态(默认闲置）
    md_Free=true;

    //方块状态(默认存活）
    m_Free1=true;

    //方块边框
    md_Rect.setWidth(m_dred_block.width()-4);
    md_Rect.setHeight(m_dred_block.height()-2);
    md_Rect.moveTo(m_dred_block_X+2, m_dred_block_Y+1);

}
