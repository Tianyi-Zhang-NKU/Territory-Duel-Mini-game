#ifndef SHOP_H
#define SHOP_H


#include "other.h"


class Shop : public other
{
public:
    // 当前阳光值，用于购买植物
    int sun;

    // 初始化商店，可能包括：
    // 设置初始阳光值（如 sun = 50）。
    // 初始化计时器（如 counter = 0）。
    // 加载卡片（如 new Card("SunFlower")）。
    Shop();

    // 必须实现（因为 QGraphicsItem 是抽象类）。
    // 定义商店的碰撞检测和绘图区域（如整个商店栏的矩形范围）。
    QRectF boundingRect() const override;

    // 必须实现。
    // 使用 QPainter 绘制商店的外观，可能包括：
    // 商店背景（如灰色栏）。
    // 阳光数量显示（如 painter->drawText(..., QString::number(sun))）。
    // 卡片槽（用于放置 Card 对象）。
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // 可选重写，用于逐帧更新商店状态。
    // phase 参数：
    // phase == 0：准备阶段（未使用）。
    // phase == 1：执行阶段（如生成阳光、更新计时器）。
    void advance(int phase) override;

    // 核心功能：在指定位置 pos 添加植物（根据名称 s）。
    // 可能的实现逻辑：
    // 检查阳光是否足够（sun >= cost）。
    // 扣除阳光（sun -= cost）。
    // 创建对应的植物对象（如 new SunFlower(pos)）。
    // 将植物添加到场景。
    void addPlant(QString s, QPointF pos);
private:
    // 计时器，可能用于控制阳光生成或商店刷新。
    int counter;
    // 时间间隔，可能用于控制阳光生成频率。
    int time;
};

#endif // SHOP_H
/*
1.代码的潜在用途:
（1）阳光管理
sun 变量存储当前阳光值，用于购买植物。
可能通过 Sun 类自动生成阳光，或通过点击阳光收集。

（2）植物购买系统
addPlant() 是核心方法，处理植物放置逻辑。
与 Card 类配合，实现“拖拽卡片 → 放置植物”的交互。

（3）计时器控制
counter 和 time 可能用于：
控制阳光生成间隔;
商店栏的动画效果（如闪烁提示）。

2. 与其他类的关系
类名	    关系
Card	商店包含多个 Card 对象，代表可购买的植物。
Plant	商店通过 addPlant() 创建 Plant 子类（如 SunFlower）。
Sun	    商店管理阳光值（sun），可能监听 Sun 的收集事件。
*/
