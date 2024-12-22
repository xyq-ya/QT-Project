#include "musicplayer.h"

MusicPlayer::MusicPlayer() {
    player_loop = new QMediaPlayer();
    player_second = new QMediaPlayer();
    output_loop = new QAudioOutput();
    output_second = new QAudioOutput();
    player_loop->setLoops(-1);
    player_loop->setAudioOutput(output_loop);
    player_second->setAudioOutput(output_second);
    player_loop->setSource(QUrl::fromLocalFile("../../sound/backgrand.mp3"));
}
void MusicPlayer::PlayBackground()
{
    player_loop->play();
}
void MusicPlayer::PlayRelese()
{
    player_second->setSource(QUrl::fromLocalFile("../../sound/pair.wav"));
    player_second->play();
}
void MusicPlayer::PlaySelect()
{
    player_second->setSource(QUrl::fromLocalFile("../../sound/select.wav"));
    player_second->play();
}
void MusicPlayer::stopLoop()
{
    player_loop->stop();
}

void MusicPlayer::PlayWrong()
{
    player_second->setSource(QUrl::fromLocalFile("../../sound/wrong.mp3"));
    player_second->play();
}
MusicPlayer::~MusicPlayer()
{
    delete(player_loop);
    delete(player_second);
    delete(output_loop);
    delete(output_second);
}
