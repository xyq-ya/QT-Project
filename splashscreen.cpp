#include "splashscreen.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>

splashscreen::splashscreen(QWidget *parent) : QWidget(parent)
{
    // 设置窗口的标题和大小
    setWindowTitle("游戏启动窗口");
    setFixedSize(300, 400);

    // 创建按钮
    startButton = new QPushButton("开始游戏", this);
    continueButton = new QPushButton("继续游戏", this);
    infoButton = new QPushButton("游戏信息", this);
    exitButton = new QPushButton("退出游戏", this);

    // 创建布局并添加按钮
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(startButton);
    layout->addWidget(continueButton);
    layout->addWidget(infoButton);
    layout->addWidget(exitButton);

    // 连接按钮点击事件到槽函数
    connect(startButton, &QPushButton::clicked, this, &splashscreen::startGame);
    connect(continueButton, &QPushButton::clicked, this, &splashscreen::continueGame);
    connect(infoButton, &QPushButton::clicked, this, &splashscreen::gameInfo);
    connect(exitButton, &QPushButton::clicked, this, &splashscreen::exitGame);
}

splashscreen::~splashscreen() {}

void splashscreen::startGame()
{
     DegreeOfDifficulty *degree_screen = new DegreeOfDifficulty();
     degree_screen->show();
     this->close();
}

void splashscreen::continueGame()
{
    // 加入继续游戏的逻辑

}

void splashscreen::gameInfo()
{
    // 这里可以显示游戏的信息
}

void splashscreen::exitGame()
{
    // 退出应用程序
    QApplication::quit();
}
