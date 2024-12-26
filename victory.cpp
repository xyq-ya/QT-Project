#include "victory.h"
#include "degreeofdifficulty.h"
#include "qpainter.h"
#include <QApplication>
#include <QVBoxLayout>

victory::victory(QWidget *parent) : QWidget(parent)
{
    // 设置窗口的标题和大小
    setWindowTitle("游戏启动窗口");
    setFixedSize(300, 400);

    // 创建按钮

    againButton = new QPushButton("再来一局", this);
    exitButton = new QPushButton("退出游戏", this);

    connect(againButton, &QPushButton::clicked, this, &victory::againGame);
    connect(exitButton, &QPushButton::clicked, this, &victory::exitGame);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(againButton);
    layout->addWidget(exitButton);

}

victory::~victory() {}

void victory::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(Qt::red);
    QFont font = painter.font();
    font.setPointSize(16);
    painter.setFont(font);
    painter.drawText(100, 70, "游戏结束");

}

void victory::againGame()
{
    DegreeOfDifficulty *degree_screen = new DegreeOfDifficulty();
    degree_screen->show();
    this->close();
}

void victory::exitGame()
{
    QApplication::quit();
}
