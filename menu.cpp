#include "menu.h"
#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>

Menu::Menu(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口的标题
    setWindowTitle("Game Menu");

    // 创建按钮
    continueButton = new QPushButton("Continue Game", this);
    restartButton = new QPushButton("Restart Game", this);
    exitButton = new QPushButton("Exit Game", this);

    // 连接按钮的点击事件到相应的槽函数
    connect(continueButton, &QPushButton::clicked, this, &Menu::onResumeButtonClicked);
    connect(restartButton, &QPushButton::clicked, this, &Menu::restartGame);
    connect(exitButton, &QPushButton::clicked, this, &Menu::onExitButtonClicked);

    // 设置按钮的布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(continueButton);
    layout->addWidget(restartButton);
    layout->addWidget(exitButton);

    // 设置布局
    setLayout(layout);
}


void Menu::restartGame()
{

    this->close();
}

void Menu::onResumeButtonClicked()
{
    emit resumeGame();  // 触发继续游戏信号
    this->close();      // 关闭暂停菜单
}

// 退出游戏按钮点击事件
void Menu::onExitButtonClicked()
{
    emit exitGame();    // 触发退出游戏信号
    this->close();      // 关闭暂停菜单
}

