#include "game.h"
#include "qtpreprocessorsupport.h"
#include "ui_game.h"
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

game::game(DifficultyLevel level, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game)
    , currentDifficulty(level)  // 初始化游戏难度
{
    ui->setupUi(this);
    player = new MusicPlayer();
    player->PlayBackground();

    // 根据难度调整地图
    createmap();

    musicToggleButton = new QPushButton("Stop Music", this);
    musicToggleButton->setGeometry(width() - 120, height() - 60, 100, 40);  // 设置按钮位置（右下角）
    connect(musicToggleButton, &QPushButton::clicked, this, &game::toggleMusic);

    // 初始化时间条
    // timeProgressBar = new QProgressBar(this);
    // timeProgressBar->setGeometry(20, 20, 1000, 50);  // 设置时间条位置和大小
    // timeProgressBar->setRange(0, timeLimit);  // 设置时间条范围
    // timeProgressBar->setValue(timeLimit);  // 设置初始值为最大值
    // timeProgressBar->setTextVisible(false);  // 隐藏文字显示

    // // 初始化定时器
    // timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &game::updateTime);
    // timer->start(1000);  // 每秒触发一次
}

game::~game()
{
    delete ui;
}

//地图以及背景绘制
void game::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制背景
    QPixmap background;
    background.load(":/images/image/background.png");
    painter.drawPixmap(0, 0, width(), height(), background);

    // 计算每个矩形的宽度和高度
    int rectWidth = width() / 12;  // 计算矩形的宽度
    int rectHeight = height() / 16; // 计算矩形的高度

    // 绘制矩形区域
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 12; ++col) {
            // 计算每个矩形的左上角坐标
            int x = col * rectWidth;
            int y = row * rectHeight;

            // 绘制障碍物
            QPixmap obstracle;
            obstracle.load(":/images/image/obstracle.jpg");
            if (map[row][col] == -1) {  // -1 表示障碍物
                painter.drawPixmap(x, y, rectWidth, rectHeight,obstracle);  // 绘制矩形
            } else {
                // 绘制普通空白区域或图片
                painter.setBrush(Qt::transparent);  // 设置矩形为透明
                painter.setPen(Qt::NoPen);  // 去除矩形边框
                painter.drawRect(x, y, rectWidth, rectHeight);  // 绘制矩形

                int imageIndex = map[row][col];
                if (imageIndex != 0) {
                    QPixmap icon = icons[imageIndex - 1];
                    if (!icon.isNull()) {
                        painter.drawPixmap(x, y, rectWidth, rectHeight, icon);  // 绘制图片
                    }
                }
            }
        }
    }
}

void game::toggleMusic()
{
    if (musicPlaying) {
        player->stopLoop();  // 停止背景音乐
        musicToggleButton->setText("Play Music");  // 更新按钮文本为 "Play Music"
    } else {
        player->PlayBackground();  // 播放背景音乐
        musicToggleButton->setText("Stop Music");  // 更新按钮文本为 "Stop Music"
    }
    musicPlaying = !musicPlaying;  // 切换音乐状态
}

void game::updateTime()
{
    if (timeLeft > 0) {
        timeLeft--;  // 每次减少1秒
        timeProgressBar->setValue(timeLeft);  // 更新时间条
    } else {
        timer->stop();  // 时间到，停止定时器
        // 你可以在这里添加游戏结束的处理逻辑
        QMessageBox::information(this, "Time's Up", "Game Over! Time's up!");
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
    // 初始化地图, 外围区域赋值为0，中间[1][1]到[14][10]为地址信息
    for(int j = 0; j < 16; j++) {
        for(int k = 0; k < 12; k++) {
            if (j == 0 || k == 0 || j == 15 || k == 11) {
                map[j][k] = 0;  // 边界
                visited[j][k] = true;
            } else {
                map[j][k] = 0;  // 默认没有图片
                visited[j][k] = false;
            }
        }
    }

    // 生成障碍物
    int obstaclesPlaced = 0;
    while (obstaclesPlaced < obstaclenum) {
        int randJ = rand() % 14 + 1;  // 随机生成行 [1, 14]
        int randK = rand() % 10 + 1;  // 随机生成列 [1, 10]

        if (map[randJ][randK] == 0 && !visited[randJ][randK]) {
            map[randJ][randK] = -1;  // 用 -1 表示障碍物
            visited[randJ][randK] = true;
            obstaclesPlaced++;
        }
    }

    // 初始化其它方块和图片
    //bool visited2[16][12] = {{false}};
    for(int j = 1; j < 15; j++) {
        for(int k = 1; k < 11; k++) {
            if (map[j][k] == 0 && !visited[j][k]) {
                int a = rand() % 24;
                if (a != 0 && !visited[j][k]) {
                    map[j][k] = a;
                    visited[j][k] = true;
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

    for (int i = 0; i < 16; ++i) {
        QString row = "";
        for (int j = 0; j < 12; ++j) {
            row += QString::number(map[i][j]) + " ";
        }
        qDebug() << row;
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

void game::setDifficulty(DifficultyLevel level)
{
    currentDifficulty = level;

    // 根据难度设置时间限制、方块数量、障碍物数量等
    switch (level) {
    case EASY:
        timeLimit = 60;
        obstaclenum = 4;
        break;
    case MEDIUM:
        timeLimit = 45;
        obstaclenum = 8;
        break;
    case HARD:
        timeLimit = 30;
        obstaclenum = 12;
        break;
    }

    timeLeft = timeLimit;  // 设置剩余时间
    timeProgressBar->setRange(0, timeLimit);  // 设置时间条范围
    timeProgressBar->setValue(timeLimit);  // 设置初始值
}
