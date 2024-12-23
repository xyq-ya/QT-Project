#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <musicplayer.h>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QPointF>
#include <iostream>
#include <vector>
#include <limits>


namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

private:
    // 存储路径的节点
    struct PathNode {
        int x, y, dir, turns;
        PathNode(int _x, int _y, int _dir, int _turns) : x(_x), y(_y), dir(_dir), turns(_turns) {}
    };

    // 存储完整路径
    using Path = std::vector<PathNode>;
    Path bestPath;
    int minTurns = std::numeric_limits<int>::max();

public:
    explicit game(QWidget *parent = nullptr);
    ~game();
    void createmap();//初始化地图
    void recreate();//更新地图信息
    void setimage();//更新ui
    void del(int k,int x,int y);//消去图片后更新数组
    bool isBlock(int col, int row);
    void dfs(int x, int y, int x2, int y2, int prevDir, int turns, Path currentPath);//递归搜索并存储路径，输出最优路径
    bool canEliminate(int x1, int y1, int x2, int y2);//判断给定两点是否可消除，减轻judge负担
    bool judge();//结合dfs判断地图上是否还有能消去的数
    void printRoute();// 打印输出dfs得到的最优路径

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::game *ui;
    enum{Null,Right,Left,Up,Down};//判断上下左右或者原点，用于规划路径
    enum{imagenum=25};
    enum{MaxSizeX=14,MaxSizeY=10};//横向14张图片，纵向10张图片
    int map[MaxSizeX + 2][MaxSizeY + 2];//地图信息,-1为障碍物，0为空白，其余为图片编号，最外围一圈为空白
    int count;//记录该次连线拐弯次数
    int num[imagenum+1];//记录每个图片的剩余次数，暂时不刷新地图便可先不做考虑

    bool visited[MaxSizeX][MaxSizeY] = {{false}};
    bool flag;//判断两个图片能否被消去
    int x1,y1,x2,y2;//坐标分别表示选中的两个图片在二元数组中的位置
    int x3,y3,x4,y4;//后两对坐标表示系统计算可被消除的一对图片

    // 方向数组，0=上, 1=右, 2=下, 3=左
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {-1, 0, 1, 0};

    struct slink
    {
        int x;
        int y;
        slink *next;
    };

    struct{
        int num;
        slink *first;
    }bucket[imagenum+1];//存放不同类型图片的坐标，bucket[i]代表第i种图片的的坐标链表，用于辅助judge（）函数
    bool transIcon;
    MusicPlayer *player;
    std::vector<QPixmap> icons;//图片组
    std::vector<QPixmap> shadow;//阴影组
    std::vector<QPointF> pressArray;
    QPixmap icon;
};


#endif // GAME_H
