#ifndef DRED_BLOCK_H
#define DRED_BLOCK_H
#include <Qpixmap>

class dred_block
{
public:
    dred_block();

    //更新方块坐标
    void updatePosition();

public:
    //方块资源对象
    QPixmap md_red_block;

    //方块坐标
    int md_red_block_X;
    int md_red_block_Y;

    //方块是否闲置
    bool md_Free;

    //方块是否存活
    bool md_Free1;

    //方块的矩形边框(用于碰撞检测)
    QRect md_Rect;



};

#endif // DRED_BLOCK_H
