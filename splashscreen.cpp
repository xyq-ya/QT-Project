#include "splashscreen.h"
#include "game.h"
#include "qpainter.h"
#include "degreeofdifficulty.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QPixmap>

splashscreen::splashscreen(QWidget *parent) : QWidget(parent)
{
    // 设置窗口的标题和大小
    setWindowTitle("游戏启动窗口");
    setFixedSize(300, 400);

    // 创建按钮
    startButton = new QPushButton("开始", this);
    continueButton = new QPushButton("继续", this);
    infoButton = new QPushButton("信息", this);
    exitButton = new QPushButton("退出", this);
    startButton->setFixedSize(180, 50);
    continueButton->setFixedSize(180, 50);
    infoButton->setFixedSize(180, 50);
    exitButton->setFixedSize(180, 50);

    //设置字体
    QFont font("Microsoft YaHei", 20, QFont::Bold);
    //设置按钮
    startButton->setFont(font);
    startButton->setStyleSheet("QPushButton {"
                               "background-image: url(:/background/image/buttons/start.png);"
                               "border: none;"
                               "text-align: center;"
                               "background-size: cover;"
                               "color: white;"
                               "background-position: center;"
                               "}");
    continueButton->setFont(font);
    continueButton->setStyleSheet("QPushButton {"
                                  "background-image: url(:/background/image/buttons/continue.png);"
                                  "border: none;"
                                  "text-align: center;"
                                  "background-size: cover;"
                                  "background-position: center;"
                                  "color: white;"
                                  "}");
    infoButton->setFont(font);
    infoButton->setStyleSheet("QPushButton {"
                              "background-image: url(:/background/image/buttons/info.png);"
                              "background-size: cover;"
                              "background-position: center;"
                              "border: none;"
                              "text-align: center;"
                              "color: white;"
                              "}");
    exitButton->setFont(font);
    exitButton->setStyleSheet("QPushButton {"
                              "background-image: url(:/background/image/buttons/exit.png);"
                              "border: none;"
                              "text-align: center;"
                              "background-size: cover;"
                              "background-position: center;"
                              "color: white;"
                              "}");

    // 创建布局并添加按钮
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(startButton, 0, Qt::AlignCenter);
    layout->addWidget(continueButton, 0, Qt::AlignCenter);
    layout->addWidget(infoButton, 0, Qt::AlignCenter);
    layout->addWidget(exitButton, 0, Qt::AlignCenter);

    // 连接按钮点击事件到槽函数
    connect(startButton, &QPushButton::clicked, this, &splashscreen::startGame);
    connect(continueButton, &QPushButton::clicked, this, &splashscreen::continueGame);
    connect(infoButton, &QPushButton::clicked, this, &splashscreen::gameInfo);
    connect(exitButton, &QPushButton::clicked, this, &splashscreen::exitGame);
}

splashscreen::~splashscreen() {}

void splashscreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制背景
    QPixmap background;
    background.load(":/background/image/back1.png");
    painter.drawPixmap(0, 0, width(), height(), background);

}

void splashscreen::startGame(){
     DegreeOfDifficulty *degree_screen = new DegreeOfDifficulty();
     degree_screen->show();
     this->close();
}

void splashscreen::continueGame(){

    for(int j=0;j<16;j++){
        for(int i=0;i<12;i++){
            recordMap[j][i]=70;
        }
    }

    QFile file("D:/code/QT-Project-zjw1226/savegame/saveMap.txt");
    // 打开文件以读取数据
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // 读取文件内容并填充到 saveMap 数组中
        for (int row = 0; row < 16; ++row) {
            QString line = in.readLine();  // 读取一行
            // 使用空格分隔行中的每一列
            QStringList columns = line.split(" ", Qt::SkipEmptyParts);

            for (int col = 0; col < 12 && col < columns.size(); ++col) {
                recordMap[row][col] = columns[col].toInt(); // 假设是整数类型
            }
        }

        file.close();
        qDebug() << "游戏读取成功";
    } else {
        qDebug() << "无法打开文件读取数据";
    }

    srand(time(nullptr));
    game *game_widget = new game(level,recordMap);
    game_widget->show();
    this->close();
}

void splashscreen::gameInfo()
{
    QMessageBox msg;

    msg.setText("版本：24.12.26");

    msg.exec();
}

void splashscreen::exitGame()
{
    QApplication::quit();
}
