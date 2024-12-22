#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <musicplayer.h>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QPointF>


namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    ~game();
    void createmap();//初始化地图
    void recreate();//更新地图信息
    void setimage();//更新ui
    bool isBlock(int col, int row);
    void dfs(int col1,int row1,int col2,int row2,int prevDir,int turns);//判断两个图片能否消去（递归搜索函数），结束后更新flag信息
    void del(int k,int x,int y);//消去图片后更新数组
    bool judge();//结合dfs判断地图上是否还有能消去的数组



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
    bool flag;//判断两个图片能否被消去
    int x1,y1,x2,y2;//坐标分别表示选中的两个图片在二元数组中的位置
    int x3,y3,x4,y4;//后两对坐标表示系统计算可被消除的一对图片
    bool visited[MaxSizeX][MaxSizeY] = {{false}};
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
