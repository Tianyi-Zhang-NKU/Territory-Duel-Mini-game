#include "mainscene.h"
#include "ui_mainscene.h"
#include "config.h"
#include <QIcon>
#include <QPainter>

#include <QTime>
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include "mshop.h"
#include <QPushButton>
#include <QMouseEvent>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
// 构造函数
{
    ui->setupUi(this);

    //点击退出菜单项 实现退出
    connect (ui->actionquit,&QAction::triggered,[=]() {
        this->close();
    });


    //调用初始化场景
    initScene();

    //启动游戏
    playGame();

    this->m_winscene =new winscene;
    this->m_losescene =new losescene;

    // 创建定时器，每隔4秒创建一个新阳光按钮
    sun_timer = new QTimer(this);
    connect(sun_timer, &QTimer::timeout, this, &MainScene::createsunBtn);
    sun_timer->start(4000);

    // 创建加农炮1卡片按钮
    m_connon1_CardBtn = new QPushButton(this);
    m_connon1_CardBtn->setGeometry(GAME_WIDTH+35, 168+35, PLANT_CARD_WIDTH, PLANT_CARD_HEIGHT);
    m_connon1_CardBtn->setIcon(QPixmap(CONNON1_PATH));
    m_connon1_CardBtn->setIconSize(QSize(PLANT_CARD_WIDTH, PLANT_CARD_HEIGHT));
    connect(m_connon1_CardBtn, &QPushButton::clicked, this, &MainScene::onPlconnon1CardClicked);

    // 创建加农炮3卡片按钮
    m_connon3_CardBtn = new QPushButton(this);
    m_connon3_CardBtn->setGeometry(GAME_WIDTH+35, 368+35, PLANT_CARD_WIDTH, PLANT_CARD_HEIGHT);
    m_connon3_CardBtn->setIcon(QPixmap(CONNON3_PATH));
    m_connon3_CardBtn->setIconSize(QSize(PLANT_CARD_WIDTH, PLANT_CARD_HEIGHT));
    connect(m_connon3_CardBtn, &QPushButton::clicked, this, &MainScene::onPlconnon3CardClicked);

    // 创建滚轮卡片按钮
    m_wheel_CardBtn = new QPushButton(this);
    m_wheel_CardBtn->setGeometry(GAME_WIDTH+35, 568+35, PLANT_CARD_WIDTH, PLANT_CARD_HEIGHT);
    m_wheel_CardBtn->setIcon(QPixmap(WHEEL_PATH));
    m_wheel_CardBtn->setIconSize(QSize(PLANT_CARD_WIDTH, PLANT_CARD_HEIGHT));
    connect(m_wheel_CardBtn, &QPushButton::clicked, this, &MainScene::onPlwheelCardClicked);

}


// 析构函数
MainScene::~MainScene()
{
    delete ui;

    // 清理所有按钮
    qDeleteAll(buttons);
    buttons.clear();
    delete sun_timer;
}



// 初始化游戏主场景函数
void MainScene::initScene(){
    //设置窗口固定尺寸
    setFixedSize (GAME_WIDTH_1,GAME_HEIGHT);

    //设置标题
    setWindowTitle (GAME_TITLE);

    //设置图标
    setWindowIcon(QIcon(":/pictures/00-icon.png"));

    //定时器设置
    m_Timer.setInterval(GAME_RATE);

}



//启动游戏函数，主要用于启动定时器并按时刷新
void MainScene::playGame(){

        //启动定时器
        m_Timer.start();

    //监听定时器发送的信号
    connect(&m_Timer,&QTimer::timeout,[=]() {

        //更新游戏中元素的坐标
        updatePosition();

        //绘制到屏幕中
        update(); //paintEvent的系统自带函数

        //红色方块出场
        red_blocktoscene();

        //碰撞检测
        //加农炮1碰撞检测
        collisionDetection_connon1();
        //加农炮3碰撞检测左前
        collisionDetection_connon3_1();
        //加农炮3碰撞检测正前
        collisionDetection_connon3_2();
        //加农炮3碰撞检测右前
        collisionDetection_connon3_3();
        //滚轮碰撞检测
        collisionDetection_wheel();

        //游戏时长计时器
        m_record++;

        // 阳光计时器，用于控制动画或消失时间(暂未实现)
        // sun_counter++;

        //判断游戏是否胜利并跳转界面
        int m_n_1=0;
        m_n_1=m_game();
        m_game_change(m_n_1);

    });
}



//更新屏幕函数
void MainScene::updatePosition()
{

    //加农炮1
    //发射加农炮1子弹
    m_connon1.shoot();
    //计算所有非空闲子弹的当前坐标
    for(int i=0;i<CONNON1_BULLET_NUM;i++)
    {
        //如果非空闲,计算发射位置
        if(m_connon1.m_bullets[i].m_Free == false){
            m_connon1.m_bullets[i].updatePosition();
        }
    }

    //加农炮3
    //发射加农炮3子弹
    m_connon3.shoot();
    //计算所有左前非空闲子弹的当前坐标
    for(int i=0;i<CONNON3_BULLET_NUM_1;i++)
    {
        //如果非空闲,计算发射位置
        if(m_connon3.m_bullets_1[i].m_Free == false){
            m_connon3.m_bullets_1[i].updatePosition();
        }
    }
    //计算所有正前非空闲子弹的当前坐标
    for(int i=0;i<CONNON3_BULLET_NUM_2;i++)
    {
        //如果非空闲,计算发射位置
        if(m_connon3.m_bullets_2[i].m_Free == false){
            m_connon3.m_bullets_2[i].updatePosition();
        }
    }
    //计算所有右前非空闲子弹的当前坐标
    for(int i=0;i<CONNON3_BULLET_NUM_3;i++)
    {
        //如果非空闲,计算发射位置
        if(m_connon3.m_bullets_3[i].m_Free == false){
            m_connon3.m_bullets_3[i].updatePosition();
        }
    }

    //滚轮
    m_wheel.updatePosition();

    // 更新加农炮1的冷却状态和射击
    for(auto plant1 : m_plconnon1){
        plant1->updateCooling();
        plant1->shoot();

        // 更新子弹位置
        for(int i=0; i<CONNON1_BULLET_NUM; i++){
            if(!plant1->m_bullets[i].m_Free){
                plant1->m_bullets[i].updatePosition();
            }
        }
    }

    // 更新加农炮3的冷却状态和射击
    for(auto plant2 : m_plconnon3){
        plant2->updateCooling();
        plant2->shoot();

        // 更新各种子弹位置
        for(int i=0; i<CONNON3_BULLET_NUM_1; i++){
            if(!plant2->m_bullets_1[i].m_Free){
                plant2->m_bullets_1[i].updatePosition();
            }
        }
        for(int i=0; i<CONNON3_BULLET_NUM_2; i++){
            if(!plant2->m_bullets_2[i].m_Free){
                plant2->m_bullets_2[i].updatePosition();
            }
        }
        for(int i=0; i<CONNON3_BULLET_NUM_3; i++){
            if(!plant2->m_bullets_3[i].m_Free){
                plant2->m_bullets_3[i].updatePosition();
            }
        }
    }

    // 更新滚轮的冷却状态
    for(auto plant3 : m_plwheel){
        plant3->updateCooling();
        plant3->updatePosition();
    }
}




//绘制屏幕
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //this指针，表示画到当前屏幕

    //绘制背景图
    painter.drawPixmap(0,0,m_map.m_map);

    //商店阳光对象
    painter.drawPixmap(GAME_WIDTH,0,m_shop.shop_sun);

    // 绘制阳光值
    // 设置字体颜色，可共用
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(GAME_WIDTH+55, 150, QString("%1").arg(sun_sum));

    //商店卡片对象
    painter.drawPixmap(GAME_WIDTH,168,m_shop.shop_card);

    //卡片对象1加农炮1
    painter.drawPixmap(GAME_WIDTH+4,168,m_card.m_card);
    if (sun_sum < CONNON1_COST) { // 阳光低于100时
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255, 0, 0, 100)); // 半透明红色
        painter.drawRect(GAME_WIDTH+4, 168, 142, 198); // 卡片区域绘制红色笼罩
    }
    painter.drawText(GAME_WIDTH+55, 350, QString("%1").arg(CONNON1_COST));

    //卡片对象2加农炮3
    painter.drawPixmap(GAME_WIDTH+4,368,m_card.m_card);
    if (sun_sum < CONNON3_COST) { // 阳光低于200时
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255, 0, 0, 100)); // 半透明红色
        painter.drawRect(GAME_WIDTH+4, 368, 142, 198); // 卡片区域绘制红色笼罩
    }
    painter.drawText(GAME_WIDTH+55, 550, QString("%1").arg(CONNON3_COST));

    //卡片对象3滚轮
    painter.drawPixmap(GAME_WIDTH+4,568,m_card.m_card);
    if (sun_sum < WHEEL_COST) { // 阳光低于150时
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255, 0, 0, 100)); // 半透明红色
        painter.drawRect(GAME_WIDTH+4, 568, 142, 198); // 卡片区域绘制红色笼罩
    }
    painter.drawText(GAME_WIDTH+55, 750, QString("%1").arg(WHEEL_COST));

    //绘制红色方块
    for(int i=0;i<BLOCK_NUM;i++)
    {
        //如果非空闲且存活,绘制红色方块
        if(m_block[i].m_Free == false && m_block[i].m_Free1 == true){
            painter.drawPixmap(m_block[i].m_red_block_X , m_block[i].m_red_block_Y , m_block[i].m_red_block);
        }
    }

    //绘制深红色方块
    //painter.drawPixmap(temp_dblock.m_dred_block_X,temp_dblock.m_dred_block_Y,temp_dblock.m_dred_block);

    //绘制敌机
    //painter.drawPixmap(m_enemy_plane.m_enemy_plane_posX,m_enemy_plane.m_enemy_plane_posY,m_enemy_plane.m_enemy_plane);

    //绘制云朵
    //painter.drawPixmap(m_cloud.m_cloud_posX,m_cloud.m_cloud_posY,m_cloud.m_cloud);

    // 绘制已种植的加农炮1
    for(auto plant1 : m_plconnon1){
        painter.drawPixmap(plant1->m_connon1_posX, plant1->m_connon1_posY, plant1->m_connon1);

        // 如果冷却中，绘制灰色遮罩
        if (plant1->isCooling()) {
            painter.setBrush(QColor(128, 128, 128, static_cast<int>(plant1->m_cooldownOpacity * 180))); // 灰色遮罩
            painter.setPen(Qt::NoPen);
            painter.drawRect(plant1->m_connon1_posX, plant1->m_connon1_posY,
                             plant1->m_connon1.width(), plant1->m_connon1.height());}

        // 绘制子弹
        for(int i=0; i<CONNON1_BULLET_NUM; i++){
            if(!plant1->m_bullets[i].m_Free){
                painter.drawPixmap(plant1->m_bullets[i].m_bullet_X,
                                   plant1->m_bullets[i].m_bullet_Y,
                                   plant1->m_bullets[i].m_bullet);
            }
        }
    }

    // 绘制已种植的加农炮3
    for(auto plant2 : m_plconnon3){
        painter.drawPixmap(plant2->m_connon3_posX, plant2->m_connon3_posY, plant2->m_connon3);

        // 如果冷却中，绘制灰色遮罩
        if (plant2->isCooling()) {
            painter.setBrush(QColor(128, 128, 128, static_cast<int>(plant2->m_cooldownOpacity * 180))); // 灰色遮罩
            painter.setPen(Qt::NoPen);
            painter.drawRect(plant2->m_connon3_posX, plant2->m_connon3_posY,
                             plant2->m_connon3.width(), plant2->m_connon3.height());}

        // 绘制各种子弹
        for(int i=0; i<CONNON3_BULLET_NUM_1; i++){
            if(!plant2->m_bullets_1[i].m_Free){
                painter.drawPixmap(plant2->m_bullets_1[i].m_bullet_X,
                                   plant2->m_bullets_1[i].m_bullet_Y,
                                   plant2->m_bullets_1[i].m_bullet);
            }
        }
        for(int i=0; i<CONNON3_BULLET_NUM_2; i++){
            if(!plant2->m_bullets_2[i].m_Free){
                painter.drawPixmap(plant2->m_bullets_2[i].m_bullet_X,
                                   plant2->m_bullets_2[i].m_bullet_Y,
                                   plant2->m_bullets_2[i].m_bullet);
            }
        }
        for(int i=0; i<CONNON3_BULLET_NUM_3; i++){
            if(!plant2->m_bullets_3[i].m_Free){
                painter.drawPixmap(plant2->m_bullets_3[i].m_bullet_X,
                                   plant2->m_bullets_3[i].m_bullet_Y,
                                   plant2->m_bullets_3[i].m_bullet);
            }
        }
    }

    // 绘制已种植的滚轮
    for(auto plant3 : m_plwheel){
        painter.drawPixmap(plant3->m_wheel_posX, plant3->m_wheel_posY, plant3->m_wheel);

        // 如果冷却中，绘制灰色遮罩
        if (plant3->isCooling()) {
            painter.setBrush(QColor(128, 128, 128, static_cast<int>(plant3->m_cooldownOpacity * 180))); // 灰色遮罩
            painter.setPen(Qt::NoPen);
            painter.drawRect(plant3->m_wheel_posX, plant3->m_wheel_posY,
                             plant3->m_wheel.width(), plant3->m_wheel.height());}

    }

    // 绘制正在拖拽的加农炮1预览
    if(m_selectedPlconnon1){
        painter.setOpacity(0.7); // 半透明效果
        painter.drawPixmap(QCursor::pos().x()-m_selectedPlconnon1->m_connon1.width()/2,
                           QCursor::pos().y()-m_selectedPlconnon1->m_connon1.height()/2,
                           m_selectedPlconnon1->m_connon1);
        painter.setOpacity(1.0);
    }

    // 绘制正在拖拽的加农炮3预览
    if(m_selectedPlconnon3){
        painter.setOpacity(0.7); // 半透明效果
        painter.drawPixmap(QCursor::pos().x()-m_selectedPlconnon3->m_connon3.width()/2,
                           QCursor::pos().y()-m_selectedPlconnon3->m_connon3.height()/2,
                           m_selectedPlconnon3->m_connon3);
        painter.setOpacity(1.0);
    }

    // 绘制正在拖拽的滚轮预览
    if(m_selectedPlwheel){
        painter.setOpacity(0.7); // 半透明效果
        painter.drawPixmap(QCursor::pos().x()-m_selectedPlwheel->m_wheel.width()/2,
                           QCursor::pos().y()-m_selectedPlwheel->m_wheel.height()/2,
                           m_selectedPlwheel->m_wheel);
        painter.setOpacity(1.0);
    }

}



//游戏胜利失败判断函数
int MainScene::m_game( )// 正常来讲此函数应该由“bool”来编写，但由于有三种不同情况遂使用“int”
{
    int m_n=0;
    //超时游戏判负
    if(GAME_TIME<=m_record){
        return 1;
    }
    for(int i=0;i<BLOCK_NUM;i++){
        if(m_block[i].m_Free == false && m_block[i].m_Free1 == true ){
            m_n++;
        }
    }
    for(int i=0;i<DBLOCK_NUM;i++){
        if(md_block[i].md_Free == false && md_block[i].m_Free1 == true){
            m_n++;
        }
    }
    //在游戏时间内敌人方块数量已经减少到预设标准，游戏胜利
    if(m_n<=GAME_WIN){
        return 2;
    }
    //在游戏时间内未完成要求，游戏继续
    return 3;
}

//游戏胜利失败画面跳转函数
void MainScene::m_game_change(int n)
{
    if(n==1){
        this->m_losescene->show();
        this->hide();
        qDebug() << "游戏失败";
    }
    if(n==2){
        this->m_winscene->show();
        this->hide();
        qDebug() << "游戏胜利";
    }
    return;
}



//红色方块出场
void MainScene::red_blocktoscene()
{
    for(int i=0;i<BLOCK_NUM;i++){
        //如果是空闲且存活红色方块 出场
        if(m_block[i].m_Free && m_block[i].m_Free1){
            m_block[i].m_Free=false;

            //坐标
            m_block[i].m_red_block_X = 2+(i-(i/18)*18)*30;
            m_block[i].m_red_block_Y = 3+(i/18)*30;

            //更新边框
            m_block[i].m_Rect.moveTo(m_block[i].m_red_block_X, m_block[i].m_red_block_Y);
        }
    }
}




//碰撞检测系列函数体的实现
//加农炮1子弹与红色方块碰撞检测
void MainScene::collisionDetection_connon1()
{
    //遍历所有非空闲的红色方块
    for(int i = 0 ;i <BLOCK_NUM;i++){
        if(!m_block[i].m_Free1){
            //已死亡红色方块跳转下一次循环
            continue;
        }
        //遍历所有非空闲的加农炮1子弹
        for(auto plant1 : m_plconnon1){
            for(int j=0;j<CONNON1_BULLET_NUM;j++){
                if(plant1->m_bullets[j].m_Free){
                    //空闲子弹跳转下一次循环
                    continue;
                }
                //如果子弹矩形框和红色方块矩形框相交,发生碰撞,子弹变为空闲状态，红色方块死亡
                if(m_block[i].m_Rect.intersects(plant1->m_bullets[j].m_Rect)){
                    m_block[i].m_Free1 = false;//红色方块死亡
                    plant1->m_bullets[j].m_Free = true;
                }
            }
        }
    }
}

//加农炮3左前子弹与红色方块碰撞检测
void MainScene::collisionDetection_connon3_1()
{
    //遍历所有非空闲的红色方块
    for(int i = 0 ;i <BLOCK_NUM;i++){
        if(!m_block[i].m_Free1){
            //已死亡红色方块跳转下一次循环
            continue;
        }
        //遍历所有非空闲的加农炮3左前子弹
        for(auto plant2 : m_plconnon3){
            for(int j=0;j<CONNON3_BULLET_NUM_1;j++){
                if(plant2->m_bullets_1[j].m_Free){
                    //空闲子弹跳转下一次循环
                    continue;
                }
                //如果子弹矩形框和红色方块矩形框相交,发生碰撞,子弹变为空闲状态，红色方块死亡
                if(m_block[i].m_Rect.intersects(plant2->m_bullets_1[j].m_Rect)){
                    m_block[i].m_Free1 = false;//红色方块死亡
                    plant2->m_bullets_1[j].m_Free = true;
                }
            }
        }
    }
}

//加农炮3正前子弹与红色方块碰撞检测
void MainScene::collisionDetection_connon3_2()
{
    //遍历所有非空闲的红色方块
    for(int i = 0 ;i <BLOCK_NUM;i++){
        if(!m_block[i].m_Free1){
            //已死亡红色方块跳转下一次循环
            continue;
        }
        //遍历所有非空闲的加农炮3正前子弹
        for(auto plant2 : m_plconnon3){
            for(int j=0;j<CONNON3_BULLET_NUM_2;j++){
                if(plant2->m_bullets_2[j].m_Free){
                    //空闲子弹跳转下一次循环
                    continue;
                }
                //如果子弹矩形框和红色方块矩形框相交,发生碰撞,子弹变为空闲状态，红色方块死亡
                if(m_block[i].m_Rect.intersects(plant2->m_bullets_2[j].m_Rect)){
                    m_block[i].m_Free1 = false;//红色方块死亡
                    plant2->m_bullets_2[j].m_Free = true;
                }
            }
        }
    }
}

//加农炮3右前子弹与红色方块碰撞检测
void MainScene::collisionDetection_connon3_3()
{
    //遍历所有非空闲的红色方块
    for(int i = 0 ;i <BLOCK_NUM;i++){
        if(!m_block[i].m_Free1){
            //已死亡红色方块跳转下一次循环
            continue;
        }
        //遍历所有非空闲的加农炮3右前子弹
        for(auto plant2 : m_plconnon3){
            for(int j=0;j<CONNON3_BULLET_NUM_3;j++){
                if(plant2->m_bullets_3[j].m_Free){
                    //空闲子弹跳转下一次循环
                    continue;
                }
                //如果子弹矩形框和红色方块矩形框相交,发生碰撞,子弹变为空闲状态，红色方块死亡
                if(m_block[i].m_Rect.intersects(plant2->m_bullets_3[j].m_Rect)){
                    m_block[i].m_Free1 = false;//红色方块死亡
                    plant2->m_bullets_3[j].m_Free = true;
                }
            }
        }
    }
}

//滚轮碰撞检测
void MainScene::collisionDetection_wheel()
{
    //遍历所有非空闲的红色方块
    for(int i = 0 ;i <BLOCK_NUM;i++){
        if(!m_block[i].m_Free1){
            //已死亡红色方块跳转下一次循环
            continue;
        }

        //如果滚轮矩形框和红色方块矩形框相交,发生碰撞,子弹变为空闲状态，红色方块死亡
        for(auto plant3 : m_plwheel){
            if(m_block[i].m_Rect.intersects(plant3->m_Rect)){
                m_block[i].m_Free1 = false;//红色方块死亡
            }
        }


    }
}




//阳光按钮的创建
void MainScene::createsunBtn()
{
    // 如果按钮数量达到上限，不再创建
    if(buttons.size() >= MAX_BUTTONS) {
        return;
    }

    //buttons.size() 是获取 QList 容器中元素数量的方法，同时也可用于容器管理：
    //buttons.append(button);  // 添加按钮到列表
    //buttons.removeOne(button); // 从列表移除按钮

    // 初始化随机数生成器（貌似没用上）
    QTime time = QTime::currentTime();
    srand(time.msec() + time.second() * 1000);

    // 创建新按钮
    QPushButton *button = new QPushButton(this);
    QPixmap pix;
    pix.load(SUN_PATH);

    // 设置按钮大小
    //button->setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
    //设置按钮固定尺寸
    button->setFixedSize (pix.width(),pix.height());
    //设置不规则样式
    button->setStyleSheet("QPushButton{border:0px;)");
    //设置图标
    button->setIcon (pix);
    //设置图标大小
    button->setIconSize (QSize(pix.width(),pix.height()));

    // 随机位置
    int x = rand() % (GAME_WIDTH - BUTTON_SIZE);
    int y = rand() % (GAME_HEIGHT - BUTTON_SIZE);
    button->move(x, y);

    // 连接点击信号
    connect(button, &QPushButton::clicked, this, &MainScene::removesunBtn);

    // 显示按钮
    button->show();

    // 添加到按钮列表
    buttons.append(button);

    qDebug() << "一个阳光随机生成在了坐标 (" << x << "," << y << ")点处";

}
//阳光按钮的移除
void MainScene::removesunBtn()
{
    // 获取发送信号的按钮
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if(button) {
        // 从列表中移除
        buttons.removeOne(button);

        // 删除按钮
        button->deleteLater();

        qDebug() << "随机阳光移除";
        sun_sum+=25;
        qDebug() << "获得25阳光";
    }
}




// 卡片点击处理
// 鼠标事件处理
void MainScene::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_selectedPlconnon1){
        // 可以在这里添加加农炮1跟随鼠标的效果
    }
    if(event->button() == Qt::LeftButton && m_selectedPlconnon3){
        // 可以在这里添加加农炮3跟随鼠标的效果
    }
    if(event->button() == Qt::LeftButton && m_selectedPlwheel){
        // 可以在这里添加滚轮跟随鼠标的效果
    }
    QMainWindow::mousePressEvent(event);
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    if(m_selectedPlconnon1){
        // 更新加农炮1预览位置
    }
    if(m_selectedPlconnon3){
        // 更新加农炮3预览位置
    }
    if(m_selectedPlwheel){
        // 更新滚轮预览位置
    }
    QMainWindow::mouseMoveEvent(event);
}

void MainScene::mouseReleaseEvent(QMouseEvent *event)
{
    //加农炮1
    if(event->button() == Qt::LeftButton && m_selectedPlconnon1){
        QPoint pos = event->pos();
        if(canPlacePlant(pos)){
            m_selectedPlconnon1->setPosition(pos.x(), pos.y());
            m_selectedPlconnon1->startCooling();
            m_plconnon1.append(m_selectedPlconnon1);

            // 开始卡片冷却
            m_connon1_CardBtn->setEnabled(false);
            //冷却未结束无法点击的机制
            QTimer::singleShot(CONNON1_COOLDOWN, [this](){
                m_connon1_CardBtn->setEnabled(true);
            });

            m_selectedPlconnon1 = nullptr;
        }
    }
    //加农炮3
    if(event->button() == Qt::LeftButton && m_selectedPlconnon3){
        QPoint pos = event->pos();
        if(canPlacePlant(pos)){
            m_selectedPlconnon3->setPosition(pos.x(), pos.y());
            m_selectedPlconnon3->startCooling();
            m_plconnon3.append(m_selectedPlconnon3);

            // 开始卡片冷却
            m_connon3_CardBtn->setEnabled(false);
            QTimer::singleShot(CONNON3_COOLDOWN, [this](){
                m_connon3_CardBtn->setEnabled(true);
            });

            m_selectedPlconnon3 = nullptr;
        }
    }
    //滚轮
    if(event->button() == Qt::LeftButton && m_selectedPlwheel){
        QPoint pos = event->pos();
        if(canPlacePlant(pos)){
            m_selectedPlwheel->setPosition(pos.x(), pos.y());
            m_selectedPlwheel->startCooling();
            m_plwheel.append(m_selectedPlwheel);

            // 开始卡片冷却
            m_wheel_CardBtn->setEnabled(false);
            QTimer::singleShot(WHEEL_COOLDOWN, [this](){
                m_wheel_CardBtn->setEnabled(true);
            });

            m_selectedPlwheel = nullptr;
        }
    }
    QMainWindow::mouseReleaseEvent(event);
}

// 判断位置是否可以种植
bool MainScene::canPlacePlant(QPoint pos)
{
    // 简单检查是否在主游戏区域内
    return pos.y() > 0 && pos.y() < GAME_HEIGHT && pos.x() > 50 && pos.x() < GAME_WIDTH-50;
}

// 加农炮1卡片点击
void MainScene:: onPlconnon1CardClicked()
{
    if(sun_sum >= CONNON1_COST && !m_selectedPlconnon1){
        m_selectedPlconnon1 = new connon1();// 创建新植物的底层逻辑！！！！！
        sun_sum -= CONNON1_COST;
        update();
    }
}

// 加农炮3卡片点击
void MainScene:: onPlconnon3CardClicked()
{
    if(sun_sum >= CONNON3_COST && !m_selectedPlconnon3){
        m_selectedPlconnon3 = new connon3();// 创建新植物的底层逻辑！！！！！
        sun_sum -= CONNON3_COST;
        update();
    }
}

// 滚轮卡片点击
void MainScene:: onPlwheelCardClicked()
{
    if(sun_sum >= WHEEL_COST && !m_selectedPlwheel){
        m_selectedPlwheel = new wheel();// 创建新植物的底层逻辑！！！！！
        sun_sum -= WHEEL_COST;
        update();
    }
}
