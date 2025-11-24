#include "mshop.h"
#include "config.h"

Mshop::Mshop() {
    /*
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
*/
    //初始化加载商店阳光对象
    shop_sun.load(SHOP_SUN_PATH);

    //初始化加载商店卡片对象
    shop_card.load(SHOP_CARD_PATH);

}
