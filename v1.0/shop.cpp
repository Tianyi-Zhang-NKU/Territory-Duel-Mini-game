#include "shop.h"
#include "card.h"
#include "sun.h"
/*
#include "sunflower.h"
#include "peashooter.h"
#include "cherrybomb.h"
#include "wallnut.h"
#include "snowpea.h"
#include "potatomine.h"
#include "repeater.h"
#include "basiczombie.h"
*/

// 功能：
// 设置初始阳光值为 200。
// 初始化阳光生成计时器（counter 和 time）。
// 动态创建所有植物卡片（从 Card::name 列表加载）。
// 关键点：
// 卡片位置通过 -157 + 65 * i 计算，实现水平等距排列。
// time = int(7.0 * 1000 / 33) 表示阳光每约 7 秒生成一次（假设 advance() 每秒调用 33 次）。
Shop::Shop() {
    sun = 200;                      // 初始阳光值
    counter = 0;                    // 计时器清零
    time = int(7.0 * 1000 / 33);    // 阳光生成间隔（约 7 秒）

    // 初始化所有卡片
    Card *card = nullptr;
    for (int i = 0; i < Card::name.size(); ++i) {
        card = new Card(Card::name[i]);  // 创建卡片（如 "SunFlower"）
        card->setParentItem(this);       // 设置父对象为 Shop
        card->setPos(-157 + 65 * i, -2); // 设置卡片位置（水平排列）
    }
}


// 定义商店的边界矩形
QRectF Shop::boundingRect() const
{
    return QRectF(-270, -45, 540, 90);// 商店的碰撞区域
}



// 绘制内容：
// 商店背景（Shop.png）。
// 当前阳光值（显示在左上角）。
// 一个调试用的点（无实际作用）。
void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-270, -45, 540, 90), QPixmap(":/images/Shop.png"));// 绘制商店背景
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(QRectF(-255, 18, 65, 22), Qt::AlignCenter, QString::number(sun));// 显示阳光数量
    painter->drawPoint(-220, 0);// 调试用的点（可忽略）
}


// 功能：
// 每帧更新计时器 counter。
// 当 counter >= time 时，在场景中添加一个 Sun 对象（自动掉落阳光）。
// 关键点：
// update() 确保界面及时刷新（如阳光数值变化）。
// 阳光生成频率由 time 控制（约 7 秒一次）。
void Shop::advance(int phase) {
    if (!phase) {
        return;
    }       // 只在 phase=1 时执行
    update();                 // 请求重绘
    if (++counter >= time) {  // 计时器到达阳光生成间隔
        counter = 0;          // 重置计时器
        scene()->addItem(new Sun); // 生成一个新阳光
    }
}


// 功能：
// 检查目标位置：确保没有重复放置植物。
// 扣除阳光：根据植物类型从 sun 中扣除对应成本。
// 创建植物对象：通过 switch-case 实例化具体的植物子类。
// 添加到场景：设置位置并加入场景。
// 重置卡片冷却：找到对应的 Card 对象，重置其 counter。
// 关键点：
// 使用 Card::map 和 Card::cost 静态数据管理植物属性。
// 通过 Plant::Type 过滤场景中的植物项。
void Shop::addPlant(QString s, QPointF pos) {
    // 检查目标位置是否已有植物
    QList<QGraphicsItem *> items = scene()->items(pos);
    foreach (QGraphicsItem *item, items) {
        if (item->type() == Plant::Type) {
            return; // 如果已有植物，直接返回
        }
    }

    // 扣除阳光
    sun -= Card::cost[Card::map[s]];

    // 根据植物名称创建对应对象
/*  Plant *plant = nullptr;
    switch (Card::map[s]) {
    case 0: plant = new SunFlower; break;    // 向日葵
    case 1: plant = new Peashooter; break;   // 豌豆射手
    case 2: plant = new CherryBomb; break;   // 樱桃炸弹
    case 3: plant = new WallNut; break;      // 坚果墙
    case 4: plant = new SnowPea; break;      // 寒冰射手
    case 5: plant = new PotatoMine; break;   // 土豆地雷
    case 6: plant = new Repeater; break;     // 双发射手
    }

    // 将植物添加到场景
    plant->setPos(pos);
    scene()->addItem(plant);
*/
    // 重置对应卡片的冷却计时器
    QList<QGraphicsItem *> child = childItems();
    foreach (QGraphicsItem *item, child) {
        Card *card = qgraphicsitem_cast<Card *>(item);
        if (card->text == s) {
            card->counter = 0; // 冷却计时器归零
        }
    }

    counter = 0; // 重置商店计时器（可选）
}
