#ifndef DEGREEOFDIFFICULTY_H
#define DEGREEOFDIFFICULTY_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

enum DifficultyLevel {
    EASY,    // 简单
    MEDIUM,  // 中等
    HARD     // 困难
};

class DegreeOfDifficulty : public QWidget
{
    Q_OBJECT
public:
    DegreeOfDifficulty(QWidget *parent = nullptr);

    void setDifficulty(DifficultyLevel level);  // 设置难度
    DifficultyLevel getDifficulty() const;     // 获取当前难度
    int getTimeLimit() const;                   // 获取时间限制
    int getBlockCount() const;                  // 获取方块数量
    int getObstacleCount() const;               // 获取障碍物数量
private slots:
    void onEasyClicked();   // 简单按钮点击槽
    void onMediumClicked(); // 中等按钮点击槽
    void onHardClicked();   // 困难按钮点击槽

private:
    DifficultyLevel currentDifficulty;   // 当前难度
    int timeLimit;                       // 游戏时间限制
    int blockCount;                      // 方块数量
    int obstacleCount;                   // 障碍物数量

    QPushButton *easyButton;    // 简单按钮
    QPushButton *mediumButton;  // 中等按钮
    QPushButton *hardButton;    // 困难按钮
};

#endif // DEGREEOFDIFFICULTY_H
