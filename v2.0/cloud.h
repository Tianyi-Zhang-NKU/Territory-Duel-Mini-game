#ifndef CLOUD_H
#define CLOUD_H
#include <Qpixmap>

class cloud
{
public:
    cloud();

    //设置云朵的位置
    void setPosition(int x,int y);

    //云朵资源对象
    QPixmap m_cloud;

    //云朵坐标
    int m_cloud_posY;
    int m_cloud_posX;

};

#endif // CLOUD_H
