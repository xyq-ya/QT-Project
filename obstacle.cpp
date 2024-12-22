#include "obstacle.h"

// 默认构造函数，初始化数量为1，图片路径为空
Obstacle::Obstacle(int qty, const std::string& img) : quantity(qty), image(img) {}

// 获取障碍物的数量
int Obstacle::getQuantity() const
{
    return quantity;
}

// 设置障碍物的数量
void Obstacle::setQuantity(int qty)
{
    quantity = qty;
}

// 获取障碍物的图片路径
std::string Obstacle::getImage() const
{
    return image;
}

// 设置障碍物的图片路径
void Obstacle::setImage(const std::string& img)
{
    image = img;
}
