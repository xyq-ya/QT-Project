#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QFile>
#include "degreeofdifficulty.h"

class splashscreen : public QWidget
{
    Q_OBJECT

public:
    splashscreen(QWidget *parent = nullptr);
    ~splashscreen();

protected:
    void paintEvent(QPaintEvent *event) override;

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
    int recordMap[16][12];
    DifficultyLevel level;
};

#endif // SPLASHSCREEN_H
