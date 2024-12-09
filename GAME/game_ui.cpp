#include "game_ui.h"
#include "ui_game_ui.h"

Game_Ui::Game_Ui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game_Ui)
{
    ui->setupUi(this);
}

Game_Ui::~Game_Ui()
{
    delete ui;
}

void Game_Ui::on_pushButton_clicked()
{

}

