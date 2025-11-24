#include "wheel.h"
#include "config.h"

wheel::wheel() {

    //初始化加载滚轮对象
    m_wheel.load(WHEEL_PATH);

    //初始化测试滚轮坐标(无效)
    m_wheel_posX=-100;
        //GAME_WIDTH - 120-2;
    m_wheel_posY=-100;
        //GAME_HEIGHT - m_wheel.height();

    //滚轮边框
    m_Rect.setWidth(m_wheel.width());
    m_Rect.setHeight(m_wheel.height());
    m_Rect.moveTo(m_wheel_posX,m_wheel_posY);
}

    void wheel::updatePosition()
    {
            m_wheel_posY -= GAME_V;
            m_Rect.moveTo(m_wheel_posX, m_wheel_posY);
            return;
    }

    void wheel::setPosition(int x, int y)
    {
        m_wheel_posX=x;
        m_wheel_posY=y;
        m_Rect.moveTo(m_wheel_posX,m_wheel_posY);
        return;
    }

    void wheel::startCooling()
    {
        m_cooling = true;
        m_coolingTime = 0;
    }

void wheel::updateCooling()
    {
        if (!m_cooling) return;

        m_coolingTime += GAME_RATE;

        // 计算当前灰度遮罩的透明度，随时间线性下降
        m_cooldownOpacity = 1.0f - static_cast<float>(m_coolingTime) / WHEEL_COOLDOWN;
        if (m_cooldownOpacity < 0.0f) m_cooldownOpacity = 0.0f;

        if (m_coolingTime >= WHEEL_COOLDOWN) {
            m_cooling = false;
            m_coolingTime = 0;
            m_cooldownOpacity = 0.0f;
        }
    }


