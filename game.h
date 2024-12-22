#ifndef GAME_H
#define GAME_H

#include "degreeofdifficulty.h"
#include <QWidget>
#include <musicplayer.h>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QProgressBar>

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(DifficultyLevel level, QWidget *parent = nullptr);  // 修改构造函数，接受一个 DifficultyLevel 参数
    ~game();
    void createmap();  // 初始化地图
    void recreate();   // 更新地图信息
    void setimage();   // 更新ui
    bool isBlock(int x, int y);
    void dfs(int x, int y, int x2, int y2, int prevDir, int turns);  // 判断两个图片能否消去（递归搜索函数），结束后更新flag信息
    void del(int k, int x, int y);  // 消去图片后更新数组
    bool judge();  // 结合dfs判断地图上是否还有能消去的数组
    void setDifficulty(DifficultyLevel level);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void toggleMusic();  // 用于切换背景音乐的槽函数
    void updateTime();  //更新时间条的进度

private:
    Ui::game *ui;
    DifficultyLevel currentDifficulty;  // 当前选择的游戏难度

    enum { Null, Right, Left, Up, Down };  // 判断上下左右或者原点，用于规划路径
    enum { imagenum = 25 };
    enum { MaxSizeX = 14, MaxSizeY = 10 };  // 横向14张图片，纵向10张图片
    int map[MaxSizeX + 2][MaxSizeY + 2];  // 地图信息，加二考虑两边需要连线表示消除，其值为0时就默认为该处为空白，不为0地图信息即为对应图片标号
    int count;  // 记录该次连线拐弯次数
    int num[imagenum + 1];  // 记录每个图片的剩余次数，暂时不刷新地图便可先不做考虑
    int timeLimit = 60;
    int obstaclenum = 4;//障碍物数量
    int x1, y1, x2, y2;  // 坐标分别表示选中的两个图片在二元数组中的位置
    int x3, y3, x4, y4;  // 后两对坐标表示系统计算可被消除的一对图片
    bool flag;  // 判断两个图片能否被消去
    bool visited[MaxSizeX][MaxSizeY] = { {false} };
    struct slink {
        int x;
        int y;
        slink *next;
    };
    struct {
        int num;
        slink *first;
    } bucket[imagenum + 1];  // 存放不同类型图片的坐标，bucket[i]代表第i种图片的的坐标链表，用于辅助judge（）函数
    MusicPlayer *player;
    std::vector<QPixmap> icons;
    QPushButton *musicToggleButton;  // 按钮指针
    bool musicPlaying = true;  // 背景音乐是否正在播放的标志
    QProgressBar *timeProgressBar;  // 时间条
    QTimer *timer;                  // 定时器
    int timeLeft;                   // 剩余时间
};

#endif // GAME_H
