#include "cloud.h"
#include "config.h"

cloud::cloud() {

    //初始化加载云朵对象
    m_cloud.load(CLOUDE_PATH);

    //初始化测试云朵坐标
    m_cloud_posX=(GAME_WIDTH - m_cloud.width()) * 0.5;
    m_cloud_posY=(GAME_HEIGHT - m_cloud.height()) * 0.5;
}
