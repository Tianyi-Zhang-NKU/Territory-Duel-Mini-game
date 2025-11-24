#ifndef CONFIG_H
#define CONFIG_H
/************配置文件数据************/

/************游戏配置数据************/
#define GAME_WIDTH  544  //地图宽度（544）
#define GAME_WIDTH_1  694  //游戏真实宽度
#define GAME_HEIGHT  819  //地图高度（819）
#define GAME_TITLE  "领地之争 v1.0"  //标题
#define GAME_RATE  80  //刷新时间，单位毫秒
#define GAME_TIME  1000  //与GAME_RATE相乘，单位毫秒，为游戏最长时间(500)
#define GAME_WIN  50  //胜利标准，深红色与红色方块的总和(50)
#define GAME_V  15  //标准速度


/************背景图配置数据************/
#define MAP_PATH ":/pictures/01-background-blue" // 游戏界面背景图路径
#define CARD_PATH ":/pictures/51-card.png" // 卡片背景图路径
#define SHOP_SUN_PATH ":/pictures/52-cardshop-sun.png" // 商店阳光背景图路径
#define SHOP_CARD_PATH ":/pictures/53-cardshop.png" // 商店卡片背景图路径
#define START_MAP_PATH ":/pictures/000-start" // 开始界面背景图路径
#define WIN_MAP_PATH ":/pictures/999-win_image.png" // 游戏胜利界面背景图路径
#define LOSE_MAP_PATH ":/pictures/999-lose_image.png" // 游戏失败界面背景图路径
#define PLANT_CARD_WIDTH 80     // 植物卡片宽度
#define PLANT_CARD_HEIGHT 100   // 植物卡片高度


/************阳光配置数据************/
#define SUN_PATH ":/pictures/61-Sun.gif" // 阳光背景图路径
#define SUN_SUM0 200 // 初始阳光值
#define MAX_BUTTONS 3  // 同时存在的最大数量
#define BUTTON_SIZE 78 // 阳光（按钮）的尺寸大小


/************按钮配置数据************/
#define BUTTON_WID 100 // 标准按钮高度


/************红色方块配置数据************/
#define BLOCK_PATH ":/pictures/02-block-red" // 红色方块路径
#define BLOCK_NUM 288 // 红色方块数量


/************深红色方块配置数据************/
#define DBLOCK_PATH ":/pictures/03-block-darkred.png" // 深红色方块路径
#define DBLOCK_NUM 200 // 深红色方块数量


/************子弹配置数据************/
#define BULLET_PATH ":/pictures/04-bullet" //子弹图片路径
#define BULLET_INTERVAL 15 //发射间隔


/************加农炮1配置数据************/
#define CONNON1_PATH ":/pictures/11-cannon-1" // 加农炮1图片路径
#define CONNON1_BULLET_NUM 36 // 加农炮1弹匣子弹数量
#define CONNON1_COST 100      // 加农炮1种植消耗阳光
#define CONNON1_COOLDOWN 5000 // 加农炮1冷却时间(ms)


/************加农炮3配置数据************/
#define CONNON3_PATH ":/pictures/12-cannon-3" // 加农炮3图片路径
#define CONNON3_COST 200      // 加农炮3种植消耗阳光
#define CONNON3_BULLET_NUM_1 36 // 加农炮3左前弹匣子弹数量
#define CONNON3_BULLET_NUM_2 36 // 加农炮3正前弹匣子弹数量
#define CONNON3_BULLET_NUM_3 36 // 加农炮3右前弹匣子弹数量
#define CONNON3_COOLDOWN 5000 // 加农炮3冷却时间(ms)


/************滚轮配置数据************/
#define WHEEL_PATH ":/pictures/21-wheel" // 滚轮图片路径
#define WHEEL_COST 150      // 滚轮种植消耗阳光
#define WHEEL_COOLDOWN 5000 // 滚轮冷却时间(ms)


/************敌机配置数据************/
#define ENEMY_PLANE_PATH ":/pictures/31-warplane-red" // 敌机图片路径


/************敌方云朵配置数据************/
#define CLOUDE_PATH ":/pictures/41-cloud" // 敌方云朵图片路径



#endif // CONFIG_H
