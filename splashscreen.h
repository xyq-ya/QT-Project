#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "degreeofdifficulty.h"
#include <QWidget>
#include <QPushButton>

class splashscreen : public QWidget
{
    Q_OBJECT

public:
    splashscreen(QWidget *parent = nullptr);
    ~splashscreen();

private slots:
    void startGame();      // 开始游戏按钮的槽函数
    void continueGame();   // 继续游戏按钮的槽函数
    void gameInfo();       // 游戏信息按钮的槽函数
    void exitGame();       // 退出按钮的槽函数

private:
    QPushButton *startButton;
    QPushButton *continueButton;
    QPushButton *infoButton;
    QPushButton *exitButton;
};

#endif // SPLASHSCREEN_H
