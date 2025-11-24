#include "sun.h"
#include "shop.h"



// 两种构造方式：
// 默认构造：从屏幕顶部随机x位置下落
// 指定位置构造：从特定位置(如向日葵)生成，带小范围随机偏移
// 使用 QMovie 加载GIF动画实现阳光闪烁效果
// 精确计算了下落速度和存在时间
Sun::Sun()// 默认构造函数
{
    // 设置随机目标位置(地面位置)
    dest = QPointF(290 + rand() % (82 * 7), 130 + rand() % (98 * 5));
    // 初始位置在目标x坐标，y=70(屏幕顶部附近)
    setPos(QPointF(dest.x(), 70));
    // 计算下落速度(60像素/秒 * 50ms/帧 ÷ 1000ms)
    speed = 60.0 * 50 / 1000;
    counter = 0;  // 计时器清零
    time = int(10.0 * 1000 / 33);  // 存在时间约10秒(假设每秒33帧)
    movie = new QMovie(":/images/Sun.gif");  // 加载阳光动画
    movie->start();  // 开始播放动画
    setAcceptedMouseButtons(Qt::LeftButton);  // 只接受左键点击
}

Sun::Sun(QPointF pos)// 指定位置构造函数
{
    // 在传入位置附近随机偏移
    dest = QPointF(pos.x() + rand() % 30 - 15, pos.y() + rand() % 30 + 15);
    setPos(QPointF(dest.x(), pos.y()));  // 初始位置
    speed = 60 * 50 / 1000;  // 同默认构造
    counter = 0;
    time = int(10.0 * 1000 / 33);
    movie = new QMovie(":/images/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}


// 确保 QMovie 资源被正确释放
// 防止内存泄漏
Sun::~Sun()
{
    if (movie)
        delete movie;// 释放动画资源
}


// 定义阳光的点击和碰撞区域
// 中心点为(0,0)，向四周扩展35像素
QRectF Sun::boundingRect() const
{
    return QRectF(-35, -35, 70, 70);// 70x70的正方形区域
}


// 绘制当前帧的GIF动画
// 使用 boundingRect() 作为绘制区域
// 忽略未使用的参数
void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());
}


// 点击阳光后：
// 找到场景中的商店对象
// 给商店增加25阳光
// 准备销毁自己
// 阻止事件继续传播
void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    // 获取场景中的Shop对象(假设位于(300,15))
    Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(300, 15))[0]);
    shop->sun += 25;  // 增加25阳光值
    counter = time;   // 立即标记为可销毁状态
    event->setAccepted(true);  // 事件已处理
}


// 每帧执行：
// 更新时间计数器
// 超时(约10秒)后自毁
// 未到达目标位置则继续下落
void Sun::advance(int phase)
{
    if (!phase)  // 只在phase=1时执行
        return;
    update();  // 请求重绘

    if (++counter >= time)  // 超时检查
        delete this;  // 自毁
    else if (y() < dest.y())  // 下落过程
        setY(y() + speed);  // 按速度下落
}
