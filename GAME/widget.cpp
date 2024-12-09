#include "widget.h"
#include "ui_widget.h"
#include "game_ui.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    Game_Ui *game_widget = new Game_Ui();
    game_widget->show();
    this->close();
}

