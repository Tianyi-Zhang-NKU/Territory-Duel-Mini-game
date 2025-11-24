#ifndef SUN_H
#define SUN_H

#include "other.h"

class Sun : public other
{
public:
    // 提供了两种构造方式：默认构造和指定初始位置构造
    // 析构函数被显式重写，可能用于释放 QMovie 资源
    Sun();  // 默认构造函数
    Sun(QPointF pos);  // 带位置参数的构造函数
    ~Sun() override;  // 析构函数

    // 必须实现，定义阳光的碰撞检测区域
    // 通常返回阳光图片的边界矩形
    QRectF boundingRect() const override;

    // 必须实现，用于绘制阳光的外观
    // 可能会使用 QMovie 来显示动画效果
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // 处理鼠标点击事件
    // 当玩家点击阳光时，可能会触发收集阳光的逻辑
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // 用于逐帧更新阳光状态
    // 可能实现阳光的下落动画或自动消失逻辑
    void advance(int phase) override;

private:

    // 用于加载和播放阳光的动画
    QMovie *movie;
    // 阳光的目标位置（可能是最终下落位置）
    QPointF dest;
    // 计时器，用于控制动画或消失时间
    int counter;
    // 时间间隔，可能控制阳光存在时间
    int time;
    // 阳光下落的速度
    qreal speed;
};

#endif // SUN_H
// 在场景中显示阳光（可能有动画效果）
// 实现阳光的下落运动
// 处理玩家点击收集阳光的交互
// 阳光一定时间后自动消失
