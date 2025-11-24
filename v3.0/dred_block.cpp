#include "dred_block.h"
#include "config.h"

dred_block::dred_block() {

    //加载方块资源
    md_red_block.load(DBLOCK_PATH);

    //方块坐标初始化
    md_red_block_X=0;
    md_red_block_Y=0;

    //方块状态(默认闲置）
    md_Free=true;

    //方块状态(默认存活）
    md_Free1=true;

    //方块边框
    md_Rect.setWidth(md_red_block.width()-4);
    md_Rect.setHeight(md_red_block.height()-2);
    md_Rect.moveTo(md_red_block_X+2, md_red_block_Y+1);

}
