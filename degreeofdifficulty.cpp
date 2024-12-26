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
    easyButton->setFixedSize(180, 50);
    mediumButton->setFixedSize(180, 50);
    hardButton->setFixedSize(180, 50);

    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(easyButton, 0, Qt::AlignCenter);
    layout->addWidget(mediumButton, 0, Qt::AlignCenter);
    layout->addWidget(hardButton, 0, Qt::AlignCenter);

    //设置字体
    QFont font("Microsoft YaHei", 20, QFont::Bold);
    //设置按钮
    easyButton->setFont(font);
    easyButton->setStyleSheet("QPushButton {"
                              "background-color: transparent;"
                              "background-image: url(:/background/image/buttons/continue.png);"
                              "background-size: cover;"
                              "background-position: center;"
                              "border: none;"
                              "text-align: center;"
                              "color: black;"
                              "}");
    mediumButton->setFont(font);
    mediumButton->setStyleSheet("QPushButton {"
                                "background-color: transparent;"
                                "background-image: url(:/background/image/buttons/start.png);"
                                "background-size: cover;"
                                "background-position: center;"
                                "border: none;"
                                "text-align: center;"
                                "color: black;"
                                "}");
    hardButton->setFont(font);
    hardButton->setStyleSheet("QPushButton {"
                              "background-color: transparent;"
                              "background-image: url(:/background/image/buttons/info.png);"
                              "background-size: cover;"
                              "background-position: center;"
                              "border: none;"
                              "text-align: center;"
                              "color: black;"
                              "}");

    // 连接按钮点击信号到槽函数
    connect(easyButton, &QPushButton::clicked, this, &DegreeOfDifficulty::onEasyClicked);
    connect(mediumButton, &QPushButton::clicked, this, &DegreeOfDifficulty::onMediumClicked);
    connect(hardButton, &QPushButton::clicked, this, &DegreeOfDifficulty::onHardClicked);

    for(int j=0;j<16;j++){
        for(int i=0;i<12;i++){
            map[j][i]=70;
        }
    }
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
    game *game_widget = new game(EASY,map);
    game_widget->show();
    this->close();
}

void DegreeOfDifficulty::onMediumClicked()
{
    srand(time(nullptr));
    game *game_widget = new game(MEDIUM,map);
    game_widget->show();
    this->close();
}

void DegreeOfDifficulty::onHardClicked()
{
    srand(time(nullptr));
    game *game_widget = new game(HARD,map);
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
    background.load(":/background/image/back3.png");
    painter.drawPixmap(0, 0, width(), height(), background);
}
