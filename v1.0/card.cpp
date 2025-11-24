#include "card.h"
#include "shop.h"

// 卡片名称到索引的映射（方便快速查找）
const QMap<QString, int> Card::map = {{"connon1", 0}, {"connon3", 1}, {"wheel", 2}};

// 所有卡片的名称列表
const QVector<QString> Card::name = {"connon1", "connon3", "wheel"};

// 购买每张卡片所需的阳光数量
const QVector<int> Card::cost = {100, 300, 200};

//卡片使用后的冷却时间（单位可能是帧或毫秒）
const QVector<int> Card::cool = {227, 606, 606};


// 初始化卡片名称和冷却计时器
Card::Card(QString s)
{
    text = s;
    counter = 0;
}


// 返回卡片的边界矩形（用于碰撞检测和事件处理）
QRectF Card::boundingRect() const
{
    return QRectF(-50, -30, 100, 60);
}


//绘图事件函数
void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // 缩放绘图
    painter->scale(0.6, 0.58);

    // 绘制卡片背景
    painter->drawPixmap(QRect(-50, -70, 100, 140), QPixmap(":/pictures/51-card.png"));

    // 绘制植物图标
    painter->drawPixmap(QRect(-35, -42, 70, 70), QPixmap(":/pictures/" + text + ".png"));

    // 绘制阳光消耗
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(-30, 60, QString().asprintf("%3d", cost[map[text]]));

    // 绘制冷却遮罩（如果卡片在冷却中）
    // 如果卡片在冷却中，覆盖半透明黑色遮罩，并随冷却进度减少高度
    if (counter < cool[map[text]])
    {
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(-48, -68, 98, 132 * (1 - qreal(counter) / cool[map[text]])));
    }
}


// 逻辑更新函数
// 作用：逐帧更新卡片状态（如冷却计时）
// phase=0：准备阶段（未使用）。
// phase=1：执行阶段（更新计时器并重绘）
void Card::advance(int phase)
{
    if (!phase){// 只在第二阶段（phase=1）更新
        return;
    }
    update();// 请求重绘
    if (counter < cool[map[text]]){// 冷却计时
        ++counter;
    }
}


// 逻辑：
// 1.如果卡片在冷却中，忽略点击。
// 2.如果阳光不足（shop->sun < 卡片成本），忽略点击。
// 3.否则允许后续操作（如拖拽）。
void Card::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (counter < cool[map[text]]) {
        event->setAccepted(false); // 冷却中，禁止交互
        return;
    }
    Shop *shop = qgraphicsitem_cast<Shop *>(parentItem());
    if (cost[map[text]] > shop->sun) {
        event->setAccepted(false); // 阳光不足，禁止交互
        return;
    }
    setCursor(Qt::ArrowCursor); // 设置鼠标样式
}


// 功能：实现卡片的拖拽功能。
// 拖拽时携带植物名称（text）和图标。
// 用于在场景中放置植物。
void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    // 如果移动距离太小，不触发拖拽
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
        < QApplication::startDragDistance())
        return;
    // 设置拖拽数据（植物名称和图标）
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    mime->setText(text); // 传递植物名称
    mime->setImageData(QImage(":/images/" + text + ".png"));
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(QImage));
    drag->setHotSpot(QPoint(35, 35)); // 拖拽图标的热点
    drag->exec(); // 执行拖拽
    setCursor(Qt::ArrowCursor);
}


// 释放鼠标时重置光标。
void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor); // 恢复鼠标样式
}
