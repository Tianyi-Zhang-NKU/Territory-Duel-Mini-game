#ifndef CARD_H
#define CARD_H

#include "other.h"

class Card : public other
//Card 继承自 Other，而 Other 继承自 Qt 的 QGraphicsItem，因此 Card 也是一个图形项，可以添加到 QGraphicsScene 中。
//由于 Other 未完全实现 QGraphicsItem 的纯虚函数（如 paint() 和 boundingRect()），Card 必须实现它们。
{
public:
    int counter;//用于计数或计时（冷却时间）
    QString text;//卡片上显示的文本
    Card(QString s);
    const static QMap<QString, int> map;//静态映射表，可能用于存储卡片属性（如名称到 ID 的映射）
    const static QVector<QString> name;//静态字符串列表，存储卡片名称
    const static QVector<int> cost;//静态整型列表，储卡片消耗阳光值
    const static QVector<int> cool;//静态整型列表，存储卡片冷却时间
    QRectF boundingRect() const override;//定义卡片的碰撞检测和绘图区域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;//使用 QPainter 绘制卡片的外观（如背景、文本、边框等）
    void advance(int phase) override;//可选重写，用于动画或状态更新
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;//处理鼠标按下事件（如选中卡片）
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;//处理鼠标拖动事件（如拖拽卡片）
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;//处理鼠标释放事件（如放置卡片）
private:
};

#endif // CARD_H
