#include "game.h"
#include "qtpreprocessorsupport.h"
#include "ui_game.h"
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

game::game(DifficultyLevel level, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game)
    , currentDifficulty(level)
{
    ui->setupUi(this);
    player = new MusicPlayer();
    player->PlayBackground();

    // 根据难度调整地图
    setDifficulty(level);

    //音乐开关按钮
    musicToggleButton = new QPushButton("Stop Music", this);
    musicToggleButton->setGeometry(width() - 100, height() - 40, 100, 40);  // 设置按钮位置（右下角）
    connect(musicToggleButton, &QPushButton::clicked, this, &game::toggleMusic);

    //暂停按钮
    pauseButton = new QPushButton("Menu", this);
    pauseButton->setGeometry(width() - 100, height() - 80, 100, 40);
    connect(pauseButton, &QPushButton::clicked, this, &game::openMenu);

    tips = new QPushButton("Tips", this);
    tips->setGeometry(width() - 100, height() - 120, 100, 40);
    connect(tips, &QPushButton::clicked, this, &game::giveTips);


    //游戏时间计时器
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &game::updateTime);
    timer->start(1000); // 每秒更新

    clearTimer = new QTimer(this);
    connect(clearTimer, &QTimer::timeout, this, &game::clearEliminationPath);
    //qDebug()<<"爱你，黄哥！";



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
    int rectWidth = width() / 12;
    int rectHeight = height() / 16;

    // 绘制矩形区域
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 12; ++col) {
            // 计算每个矩形的左上角坐标
            int x = col * rectWidth;
            int y = row * rectHeight;

            // 绘制障碍物
            QPixmap obstracle;
            obstracle.load(":/images/image/obstracle.jpg");

            bool isPressed = false;
            for (const auto& point : pressArray) {
                int colClicked = point.x() / rectWidth;
                int rowClicked = point.y() / rectHeight;
                if (rowClicked == row && colClicked == col) {
                    isPressed = true;
                    break;
                }
            }

            if (map[row][col] == -1) {  // -1 表示障碍物
                painter.drawPixmap(x, y, rectWidth, rectHeight,obstracle);  // 绘制矩形
            } else {
                // 绘制普通空白区域或图片
                painter.setBrush(Qt::transparent);  // 设置矩形为透明
                painter.setPen(Qt::NoPen);  // 去除矩形边框
                painter.drawRect(x, y, rectWidth, rectHeight);  // 绘制矩形

                int imageIndex = map[row][col];

                // 如果该位置被点击过（存在于 pressArray），绘制 shadow，否则绘制 icon
                if (imageIndex != 0) {
                    if (isPressed) {
                        icon = shadow[imageIndex - 1]; // 使用 shadow 图片
                    } else {
                        icon = icons[imageIndex - 1]; // 使用 icon 图片
                    }

                    // 将图片缩放到矩形大小，并绘制
                    if (!icon.isNull()) {
                        painter.drawPixmap(x, y, rectWidth, rectHeight, icon);  // 绘制图片
                    }
                }
            }
        }

        update();
    }

    // 绘制得分与连线
    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(16);
    painter.setFont(font);
    painter.drawText(10, 30, "得分：");

    painter.drawText(70, 30, QString::number(score));

    QString timeText = QString("剩余时间：%1秒").arg(remainingTime);
    painter.setPen(Qt::black);
    painter.drawText(width() - 150, 30, timeText);

    painter.setPen(QPen(Qt::black, 2));

    for (int i = 0; i < eliminationpath.size() - 1; ++i) {
        QPointF start = QPointF(
            rectWidth / 2 + rectWidth * eliminationpath[i].y(),
            rectHeight / 2 + rectHeight * eliminationpath[i].x()
            );

        QPointF end = QPointF(
            rectWidth / 2 + rectWidth * eliminationpath[i + 1].y(),
            rectHeight / 2 + rectHeight * eliminationpath[i + 1].x()
            );

        painter.drawLine(start, end);
    }

     clearTimer->start(1000);

    update();
}

void game::toggleMusic()
{
    if (musicPlaying) {
        player->stopLoop();  // 停止背景音乐
        musicToggleButton->setText("Play Music");
    } else {
        player->PlayBackground();  // 播放背景音乐
        musicToggleButton->setText("Stop Music");
    }
    musicPlaying = !musicPlaying;  // 切换音乐状态
}

void game::openMenu()
{
    // 创建并显示暂停菜单
    pauseMenu = new Menu();
    pauseMenu->show();
}

void game::giveTips()
{
    eliminationpath.clear();

    int rows = 16;
    int cols = 12;

    if(rewardtime>0){
        for (int x1 = 1; x1 < rows; ++x1)
        {
            for (int y1 = 1; y1 < cols; ++y1)
            {
                if (map[x1][y1] <= 0)
                    continue;

                for (int x2 = 1; x2 < rows; ++x2)
                {
                    for (int y2 = 1; y2 < cols; ++y2)
                    {
                        if ((x1 == x2 && y1 == y2) || map[x2][y2] <= 0)
                            continue;

                        if (map[x1][y1] == map[x2][y2])
                        {
                            if (eliminate(x1, y1, x2, y2))
                            {
                                eliminationpath.append(QPointF(x2, y2));
                                map[x1][y1] = 0;
                                map[x2][y2] = 0;

                                player->PlayRelese();
                                return;
                            }
                        }
                    }
                }
            }
        }

    }else{
        qDebug()<<"提示次数已用完";
        return;
    }
    eliminationpath.clear();
}

void game::updateTime()
{
    if (remainingTime > 0) {
        --remainingTime;
        update();
    }
}

void game::clearEliminationPath()
{
    // 清空路径坐标
    eliminationpath.clear();
    // 停止定时器，防止重复清空
    clearTimer->stop();

    update();
}

void game::mousePressEvent(QMouseEvent *event)
{
    player->PlaySelect();
    // 获取点击位置的坐标
    int clickX = event->position().x();
    int clickY = event->position().y();

    // 计算每个矩形的宽度和高度
    int rectWidth = width() / 12;  // 每个矩形的宽度
    int rectHeight = height() / 16; // 每个矩形的高度

    // 计算点击了哪个矩形
    int col= clickX / rectWidth;  // 点击位置对应的列
    int row = clickY / rectHeight; // 点击位置对应的行

    // 检查点击位置是否合法（确保点击在有效的矩形区域内）
    if (row >= 1 && row < 15 && col >= 1 && col < 11) {
        // 获取当前点击的矩形所在的 map 数组值
        int imageIndex = map[row][col];
        // 仅在该位置不是空白时处理
        if (imageIndex != 0) {
            qDebug() << "选中矩形 (" <<row << ", " << col<< "), imageIndex in icons:" << imageIndex;

            //记录连续两次点击选中的x，y坐标
            pressArray.push_back(QPointF(clickX,clickY));
            if(pressArray.size()>0){
                if(pressArray.size()==2){
                    x1=pressArray[0].x();
                    y1=pressArray[0].y();
                    x2=pressArray[1].x();
                    y2=pressArray[1].y();

                    int col1 = x1 / rectWidth;
                    int row1 = y1 / rectHeight;
                    int col2 = x2 / rectWidth;
                    int row2 = y2 / rectHeight;
                    eliminationpath.clear();
                    if(col1==col2 && row1==row2){
                        pressArray.pop_back();
                    }else{
                        flag = false;
                        if(map[row1][col1]==map[row2][col2]){

                            i = 0;
                            c = 0;
                            d = 0;
                            flag = eliminate(row1, col1, row2, col2);
                            if(flag)
                            {
                                eliminationpath.append(QPointF(row2, col2));
                                map[row1][col1] = 0;
                                map[row2][col2] = 0;
                                score++;
                                remainingTime+=rewardtime;
                                for (const QPointF& point : eliminationpath) {
                                    qDebug() << "x:" << point.x() << ", y:" << point.y();
                                }
                                player->PlayRelese();
                            }else{
                                player->PlayWrong();
                                qDebug()<<"两张图片位置不符合消除条件";
                                eliminationpath.clear();
                                }
                        }

                        pressArray.clear();  // 清空选择
                    }
                }
            }
        }
    }
}

void game::exitGame()
{
    emit exit();

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

    //初始化阴影组
    for (int i = 1; i <= 23; i++) {
        QPixmap b;
        QString imagePath = QString(":/shadow/image/shadow/%1.png").arg(i);  // 生成图片路径
        b.load(imagePath);  // 加载图片
        if (!b.isNull()) {  // 检查图片是否加载成功
            shadow.push_back(b);  // 将加载的图片加入 vector
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
    if(map[x][y]==0||map[x][y]==-1){
        return false;
    }else{
        return true;
    }
}

bool game::eliminate(int x, int y, int x2, int y2)
{
    i++;
    if(i>48)
    {
        return false;
    }

    eliminationpath.append(QPointF(x,y));

    int a = x-x2;
    int b = y-y2;
    int x1=x;
    int y1=y;

    if(x<0||x>15||y<0||y>15||x2<0||x2>15||y2<0||y2>12){
        return false;
    }

    if((a == 0 && abs(b) == 1) || (abs(a) == 1 && b == 0))
    {
        return true;
    }else{
        if(a<0){
            if(b<0){
                if(map[x+1][y]==0&&c!=-1){
                    c=1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x][y+1]==0&&d!=-1){
                    c=0;
                    d=1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x-1][y]==0&&c!=1){
                    c=-1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x][y-1]==0&&d!=1){
                    c=0;
                    d=-1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }
            }else if(b>0){
                if(map[x+1][y]==0&&c!=-1){
                    c=1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x][y-1]==0&&d!=1){
                    c=0;
                    d=-1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x][y+1]==0&&d!=-1){
                    c=0;
                    d=1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x-1][y]==0&&c!=1){
                    c=-1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }
            }else{
                if(map[x+1][y]==0&&c!=-1){
                    c=1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                        }
                }else if(map[x][y-1]==0&&d!=1){
                        c=0;
                        d=-1;
                        x1+=c;
                        y1+=d;
                        if(x1>=0&&x1<16&&y1>=0&&y1<12){
                            qDebug()<<x1<<","<<y1;
                            if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x][y+1]==0&&d!=-1){
                    c=0;
                    d=1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x-1][y]==0&&c!=1){
                    c=-1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }
            }
        }else if(a>0){
            if(b<0){
                if(map[x][y+1]==0&&d!=-1){
                    c=0;
                    d=1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x-1][y]==0&&c!=1){
                    c=-1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x][y-1]==0&&d!=1){
                    c=0;
                    d=-1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x+1][y]==0&&c!=-1){
                    c=1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }
            }else if(b>0){
                if(map[x-1][y]==0&&c!=1){
                    c=-1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x][y-1]==0&&d!=1){
                    c=0;
                    d=-1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x][y+1]==0&&d!=-1){
                    c=0;
                    d=1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x+1][y]==0&&c!=-1){
                    c=1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }
            }else{
                if(map[x][y-1]==0&&d!=1){
                    c=0;
                    d=-1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x-1][y]==0&&c!=1){
                    c=-1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x][y+1]==0&&d!=-1){
                    c=0;
                    d=1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x+1][y]==0&&c!=-1){
                    c=1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }
            }
        }else{
            if(b>0){
            if(map[x][y-1]==0&&d!=1){
                c=0;
                d=-1;
                x1+=c;
                y1+=d;
                if(x1>=0&&x1<16&&y1>=0&&y1<12){
                    qDebug()<<x1<<","<<y1;
                    if(eliminate(x1,y1,x2,y2))return true;
                }
            }else if(map[x-1][y]==0&&c!=1){
                c=-1;
                d=0;
                x1+=c;
                y1+=d;
                if(x1>=0&&x1<16&&y1>=0&&y1<12){
                    qDebug()<<x1<<","<<y1;
                    if(eliminate(x1,y1,x2,y2))return true;
                }
            }else if(map[x+1][y]==0&&c!=-1){
                c=1;
                d=0;
                x1+=c;
                y1+=d;
                if(x1>=0&&x1<16&&y1>=0&&y1<12){
                    qDebug()<<x1<<","<<y1;
                    if(eliminate(x1,y1,x2,y2))return true;
                }
            }else if(map[x][y+1]==0&&d!=-1){
                c=0;
                d=1;
                x1+=c;
                y1+=d;
                if(x1>=0&&x1<16&&y1>=0&&y1<12){
                    qDebug()<<x1<<","<<y1;
                    if(eliminate(x1,y1,x2,y2))return true;
                }
            }
            }else if(b<0){
                if(map[x][y+1]==0&&d!=-1){
                    c=0;
                    d=-1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x-1][y]==0&&c!=1){
                    c=-1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x+1][y]==0&&c!=-1){
                    c=1;
                    d=0;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }else if(map[x][y-1]==0&&d!=1){
                    c=0;
                    d=-1;
                    x1+=c;
                    y1+=d;
                    if(x1>=0&&x1<16&&y1>=0&&y1<12){
                        qDebug()<<x1<<","<<y1;
                        if(eliminate(x1,y1,x2,y2))return true;
                    }
                }
            }
        }
    }
    return false;
}

// 打印输出dfs得到的最优路径
void game::printRoute() {
    if (!bestPath.empty()) {
        std::cout << "Optimal path between (0,0) and (0,2):" << std::endl;
        for (const auto& node : bestPath) {
            std::cout << "(" << node.x << ", " << node.y << ") dir=" << node.dir << " turns=" << node.turns << std::endl;
        }
        std::cout << "Total turns: " << minTurns << std::endl;
    }
}

void game::setDifficulty(DifficultyLevel level)
{
    currentDifficulty = level;

    // 根据难度设置时间限制、方块数量、障碍物数量等
    switch (level) {
    case EASY:
        timeLimit = 60;
        obstaclenum = 4;
        tipsnum = 5;
        rewardtime = 5;
        break;
    case MEDIUM:
        timeLimit = 45;
        obstaclenum = 8;
        tipsnum = 3;
        rewardtime = 3;
        break;
    case HARD:
        timeLimit = 30;
        obstaclenum = 12;
        tipsnum = 1;
        rewardtime = 1;
        break;
    }

    createmap();
}
