#include "game.h"
#include "ui_game.h"

game::game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game)
{
    ui->setupUi(this);
    player = new MusicPlayer();
    player->PlayBackground();
}

game::~game()
{
    delete ui;
}
