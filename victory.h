#ifndef VICTORY_H
#define VICTORY_H
#include <QWidget>
#include <QPushButton>

class victory : public QWidget
{
    Q_OBJECT

public:
    victory(QWidget *parent = nullptr);
    ~victory();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void againGame();   // 继续游戏按钮的槽函数
    void exitGame();       // 退出按钮的槽函数

private:

    QPushButton *againButton;
    QPushButton *exitButton;
};

#endif // VICTORY_H
