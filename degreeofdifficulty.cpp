#include "degreeofdifficulty.h"
#include "game.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

DegreeOfDifficulty::DegreeOfDifficulty(QWidget *parent)
    : QWidget(parent),
    currentDifficulty(EASY), // 默认难度为简单
    timeLimit(60),           // 默认时间限制60秒
    blockCount(5),           // 默认方块数量5
    obstacleCount(3)         // 默认障碍物数量3
{
    setWindowTitle("难度选择");
    setFixedSize(300, 400);
    // 创建按钮
    easyButton = new QPushButton("简单", this);
    mediumButton = new QPushButton("中等", this);
    hardButton = new QPushButton("困难", this);

    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(easyButton);
    layout->addWidget(mediumButton);
    layout->addWidget(hardButton);

    //设置字体
    QFont font("Microsoft YaHei", 40, QFont::Bold);
    //设置按钮
    easyButton->setFont(font);
    easyButton->setStyleSheet("QPushButton {"
                              "background-color: transparent;"
                              "border: none;"
                              "text-align: center;"
                              "color: black;"
                              "}");
    mediumButton->setFont(font);
    mediumButton->setStyleSheet("QPushButton {"
                                "background-color: transparent;"
                                "border: none;"
                                "text-align: center;"
                                "color: black;"
                                "}");
    hardButton->setFont(font);
    hardButton->setStyleSheet("QPushButton {"
                              "background-color: transparent;"
                              "border: none;"
                              "text-align: center;"
                              "color: black;"
                              "}");

    // 连接按钮点击信号到槽函数
    connect(easyButton, &QPushButton::clicked, this, &DegreeOfDifficulty::onEasyClicked);
    connect(mediumButton, &QPushButton::clicked, this, &DegreeOfDifficulty::onMediumClicked);
    connect(hardButton, &QPushButton::clicked, this, &DegreeOfDifficulty::onHardClicked);
}

void DegreeOfDifficulty::setDifficulty(DifficultyLevel level)
{
    currentDifficulty = level;
    // 根据难度设置时间限制、方块数量、障碍物数量等
    switch (level) {
    case EASY:
        timeLimit = 60;
        blockCount = 5;
        obstacleCount = 3;
        break;
    case MEDIUM:
        timeLimit = 45;
        blockCount = 10;
        obstacleCount = 6;
        break;
    case HARD:
        timeLimit = 30;
        blockCount = 15;
        obstacleCount = 10;
        break;
    }
}

DifficultyLevel DegreeOfDifficulty::getDifficulty() const
{
    return currentDifficulty;
}

int DegreeOfDifficulty::getTimeLimit() const
{
    return timeLimit;
}

int DegreeOfDifficulty::getBlockCount() const
{
    return blockCount;
}

int DegreeOfDifficulty::getObstacleCount() const
{
    return obstacleCount;
}

void DegreeOfDifficulty::onEasyClicked()
{
    srand(time(nullptr));
    game *game_widget = new game(EASY);
    game_widget->show();
    this->close();
}

void DegreeOfDifficulty::onMediumClicked()
{
    srand(time(nullptr));
    game *game_widget = new game(MEDIUM);
    game_widget->show();
    this->close();
}

void DegreeOfDifficulty::onHardClicked()
{
    srand(time(nullptr));
    game *game_widget = new game(HARD);
    game_widget->show();
    this->close();
}

void DegreeOfDifficulty::exit()
{

}

void DegreeOfDifficulty::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制背景
    QPixmap background;
    background.load(":/images/image/back3.png");
    painter.drawPixmap(0, 0, width(), height(), background);
}
