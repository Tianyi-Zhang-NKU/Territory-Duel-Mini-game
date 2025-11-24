#include "mcard.h"
#include "config.h"

Mcard::Mcard() {

    //初始化加载商店阳光对象
    m_card.load(CARD_PATH);

}
