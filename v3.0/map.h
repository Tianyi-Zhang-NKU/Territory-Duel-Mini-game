#ifndef MAP_H
#define MAP_H
#include <Qpixmap>


class Map
{
public:
    Map();

    //背景图片对象
    QPixmap m_map;

    //设置背景坐标
    int m_map_posY;

};

#endif // MAP_H
