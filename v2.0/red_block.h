#ifndef RED_BLOCK_H
#define RED_BLOCK_H
#include <Qpixmap>

class red_block
{
public:
    red_block();

    //更新方块坐标
    void updatePosition();

public:
    //方块资源对象
    QPixmap m_red_block;

    //方块坐标
    int m_red_block_X;
    int m_red_block_Y;

    //方块是否闲置
    bool m_Free;

    //方块是否存活
    bool m_Free1;

    //方块的矩形边框(用于碰撞检测)
    QRect m_Rect;



};

#endif // RED_BLOCK_H
