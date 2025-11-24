#include "map.h"
#include "config.h"

Map::Map() {

    //初始化加载地图对象
    m_map.load(MAP_PATH);

    //初始化Y轴坐标
    m_map_posY=0;



}
