#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <QMediaPlayer>
#include <QAudioOutput>
class MusicPlayer
{
public:
    MusicPlayer();
    void PlayBackground();
    void PlaySelect();
    void PlayRelese();
    void stopLoop();
    void PlayWrong();
    ~MusicPlayer();
private:
    QMediaPlayer *player_loop;
    QMediaPlayer *player_second;
    QAudioOutput *output_loop;
    QAudioOutput *output_second;

};

#endif // MUSICPLAYER_H
