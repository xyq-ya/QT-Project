#include "game.h"
#include "qtpreprocessorsupport.h"
#include "ui_game.h"

game::game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game)
{
    ui->setupUi(this);
    player = new MusicPlayer();
    player->PlayBackground();

    createmap();





}

game::~game()
{
    delete ui;
}



//地图以及背景绘制
void game::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    //绘制背景
    QPixmap background;
    background.load(":/images/image/background.png");
    painter.drawPixmap(0, 0, width(), height(), background);

    // 计算每个矩形的宽度和高度
    int rectWidth = width() / 12;  // 计算矩形的宽度
    int rectHeight = height() / 16; // 计算矩形的高度

    //绘制矩形区域，在每个矩形区域中绘制map数组中对应编号的图片
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 12; ++col) {
            // 计算每个矩形的左上角坐标
            int x = col * rectWidth;
            int y = row * rectHeight;

            // 绘制矩形，透明的矩形
            painter.setBrush(Qt::transparent);  // 设置矩形为透明
            painter.setPen(Qt::NoPen);  // 去除矩形边框
            painter.drawRect(x, y, rectWidth, rectHeight);  // 绘制矩形

            // 获取对应的图片编号，假设 map[row][col] 存储图片编号
            int imageIndex = map[row][col];

            // 如果该位置不是空白(0)加载并绘制对应的图片
            if (imageIndex != 0) {
                QPixmap icon = icons[imageIndex - 1];
                // 将图片缩放到矩形大小，并绘制
                if (!icon.isNull()) {
                    painter.drawPixmap(x, y, rectWidth, rectHeight, icon);  // 绘制图片
                }
            }
        }
    }
}
void game::createmap(){
    //初始化图片组
    for (int i = 1; i <= 23; i++) {
        QPixmap a;
        QString imagePath = QString(":images/image/%1.png").arg(i);  // 生成图片路径
        a.load(imagePath);  // 加载图片
        if (!a.isNull()) {  // 检查图片是否加载成功
            icons.push_back(a);  // 将加载的图片加入 vector
        } else {
            qWarning() << "Failed to load image:" << imagePath;
        }
    }

    //用于标记数组元素是否已经赋值
    bool visited[16][12] = {{false}};
    //初始化地图,外围区域赋值为0，中间[1][1]到[14][10]为地址信息
    for(int j=0;j<16;j++){
        for(int k=0;k<12;k++){
            if(j==0||k==0||j==15||k==11){
                map[j][k]=0;
                visited[j][k] = true;  // 边界也标记为已访问
            }else{
                // 随机生成一个数字 a
                int a = rand() % 24;
                if (a != 0 && visited[j][k]==false) {
                    map[j][k] = a;       // 给当前位置赋值
                    visited[j][k] = true;  // 标记该位置已访问

                    // 找一个随机的未访问位置赋值为 a
                    bool assigned = false;
                    while (!assigned) {
                        int randJ = rand() % 14 + 1;  // 生成随机的行位置 [1, 14]
                        int randK = rand() % 10 + 1;  // 生成随机的列位置 [1, 10]

                        // 如果该位置未被访问，则赋值
                        if (!visited[randJ][randK]) {
                            map[randJ][randK] = a;  // 给随机位置赋值
                            visited[randJ][randK] = true;  // 标记该位置已访问
                            assigned = true;  // 赋值成功，跳出循环
                        }
                    }
                }
            }
        }
    }
}

//消除检测以及拐弯算法
bool game::isBlock(int x, int y){
    return map[x][y];
}
int prevDir = -1;
int turns = 0;
void game::dfs(int x, int y, int x2, int y2, int prevDir, int turns){
    if (x == x2 && y == y2 && turns <= 3) {
        flag = true;
        return;
    }

    visited[x][y] = true;

    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];


        if (nx > 0 && nx < MaxSizeX && ny > 0 && ny < MaxSizeY && isBlock(nx, ny) && !visited[nx][ny]) {

            if (prevDir != -1 && i != prevDir && (i - prevDir != 2 || i - prevDir != -2)) {
                turns++;
            }

            dfs(nx, ny, x2, y2, i, turns);

            if (flag) {
                return;
            }
        }
    }
}
bool game::judge(){

    for (int x = 0; x < MaxSizeX - 1; x++) {
        for (int y = 0; y < MaxSizeY - 1; y++) {

            if (x + 1 < MaxSizeX && map[x][y] == map[x + 1][y] && map[x][y] != 0) {

                flag = false;
                memset(visited, false, sizeof(visited));  // 使用 memset 来清空 visited 数组
                dfs(x, y, x + 1, y, -1, 0);
                if (flag) return true;
            }

            if (y + 1 < MaxSizeY && map[x][y] == map[x][y + 1] && map[x][y] != 0) {

                flag = false;
                memset(visited, false, sizeof(visited));  // 使用 memset 来清空 visited 数组
                dfs(x, y, x, y + 1, -1, 0);
            }
        }
    }

    return false;
}




