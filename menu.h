#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT
signals:
    void resumeGame();  // 继续游戏
    void exitGame();    // 退出游戏

public:
    Menu(QWidget *parent = nullptr);

private slots:
    void restartGame();
    void onResumeButtonClicked();
    void onExitButtonClicked();

private:
    QPushButton *continueButton;
    QPushButton *restartButton;
    QPushButton *exitButton;
};

#endif // MENU_H
