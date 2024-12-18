#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <musicplayer.h>
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
    void dfs(int x,int y,int x2,int y2,int type);//判断两个图片能否消去（递归搜索函数），结束后更新flag信息
    void del(int k,int x,int y);//消去图片后更新数组
    bool judge();//结合dfs判断地图上是否还有能消去的数组

private slots:


private:
    Ui::game *ui;
    enum{Null,Right,Left,Up,Down};//判断上下左右或者原点，用于规划路径
    enum{imagenum=25};
    enum{MaxSizeX=14,MaxSizeY=10};//横向14张图片，纵向10张图片
    int map[MaxSizeX + 2][MaxSizeY + 2];//地图信息，加二考虑两边需要连线表示消除，其值为0时就默认为该处为空白，不为0地图信息即为对应图片标号
    int count;//记录该次连线拐弯次数
    int num[imagenum+1];//记录每个图片的剩余次数，暂时不刷新地图便可先不做考虑
    bool flag;//判断两个图片能否被消去
    int x1,y1,x2,y2,x3,y3,x4,y4;//第一二对坐标分别表示选中的两个图片在二元数组中的位置，后两对坐标表示系统计算可被消除的一对图片
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
    MusicPlayer *player;
};


#endif // GAME_H
