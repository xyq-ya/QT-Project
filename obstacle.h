#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <string>

class Obstacle
{
private:
    int quantity;         // 障碍物的数量
    std::string image;    // 障碍物的图片路径

public:
    // 默认构造函数
    Obstacle(int qty = 1, const std::string& img = "");

    // 获取障碍物数量
    int getQuantity() const;

    // 设置障碍物数量
    void setQuantity(int qty);

    // 获取障碍物图片路径
    std::string getImage() const;

    // 设置障碍物图片路径
    void setImage(const std::string& img);
};

#endif // OBSTACLE_H
