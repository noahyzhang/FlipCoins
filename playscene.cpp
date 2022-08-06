#include "playscene.h"
#include "mypushbutoon.h"
#include "mycoin.h"
#include "dataconfig.h"
#include <QtDebug>
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int levelNum) {
    QString str = QString("进入了第 %1 关").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    // 初始化游戏场景
    this->setFixedSize(420, 588);
    this->setWindowIcon(QPixmap(":/Coin0001.png"));
    this->setWindowTitle("翻金币");
    // 创建菜单栏
    QMenuBar* bar = menuBar();
    bar->setNativeMenuBar(false);
    setMenuBar(bar);
    // 创建开始菜单
    QMenu* startMenu = bar->addMenu("开始");
    // 创建退出 菜单项
    QAction* quitAction = startMenu->addAction("退出");
    // 点击退出，实现退出游戏
    connect(quitAction, &QAction::triggered, [=]() {
        this->close();
    });

    // 返回按钮
    MyPushButoon* backBtn = new MyPushButoon(":/BackButton.png", ":/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());
    // 点击返回
    connect(backBtn, &MyPushButoon::clicked, [=]() {
        qDebug() << "翻金币场景中，点击了返回按钮";
        emit chooseSceneBack();
    });
    // 显示当前的关卡数
    QLabel* label = new QLabel();
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str2 = "Level: %1";
    label->setText(str2.arg(this->levelIndex));
    label->setGeometry(30, this->height() - 50, 120, 50);

    dataConfig config;
    // 初始化每个关卡的二维数组
    for (int i = 0;i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    // 胜利图片显示
    QLabel* winLabel = new QLabel();
    QPixmap tmpPix;
    tmpPix.load(":/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
//    winLabel->move(int(this->width() - tmpPix.width()*0.5), -tmpPix.height());
    winLabel->move(90, -tmpPix.height());

    // 胜利音效
    QSound* winSound = new QSound(":/LevelWinSound.wav", this);

    // 显示金币背景图案
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // 绘制背景图片
            QPixmap pix = QPixmap(":/BoardNode.png");
            pix = pix.scaled(int(pix.width()*1.5), int(pix.height()*1.5));
            QLabel* label = new QLabel();
            label->setGeometry(0, 0, pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(65+i*75, 150+j*75);

            // 创建金币
            QString str;
            if (this->gameArray[i][j] == 1) {
                str = ":/Coin0001.png";
            } else {
                str = ":/Coin0008.png";
            }
            MyCoin* coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(68+i*75, 155+j*75);

            // 给金币属性赋值
            coin->posX = i;
            coin->poxY = j;
            coin->flag = this->gameArray[i][j]; // 1 是正面. 0 是反面
            // 将金币放入到 金币的二维数组中，便于后面维护
            coinBtn[i][j] = coin;

            // 点击金币  进行翻装
            connect(coin, &MyCoin::clicked, [=](){
                // 当点击金币的时候，让所有金币不能被再此点击
                for (int i = 0; i < 4; i++) {
                    for (int j = 0;j < 4; j++) {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;
                // 反转周围
                // 周围的右侧金币反转条件
                QTimer::singleShot(300, [=]() {
                    if (coin->posX + 1 <= 3 ) {
                        coinBtn[coin->posX+1][coin->poxY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->poxY] = this->gameArray[coin->posX+1][coin->poxY] == 0 ? 1 : 0;
                    }
                    // 周围的左侧金币反装条件
                    if (coin->posX - 1 >= 0) {
                        coinBtn[coin->posX-1][coin->poxY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->poxY] = this->gameArray[coin->posX-1][coin->poxY] == 0 ? 1 : 0;
                    }
                    // 周围的上侧金币反装条件
                    if (coin->poxY + 1 <= 3) {
                        coinBtn[coin->posX][coin->poxY + 1]->changeFlag();
                        this->gameArray[coin->posX][coin->poxY+1] = this->gameArray[coin->posX][coin->poxY+1] == 0 ? 1 : 0;
                    }
                    // 周围的下侧金币反装条件
                    if (coin->poxY - 1 >= 0) {
                        coinBtn[coin->posX][coin->poxY - 1]->changeFlag();
                        this->gameArray[coin->posX][coin->poxY-1] = this->gameArray[coin->posX][coin->poxY-1] == 0 ? 1 : 0;
                    }

                    // 当反转金币结束的时候，恢复可以点击金币
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0;j < 4; j++) {
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }

                    // 判断是否胜利
                    this->isWin = true;
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (coinBtn[i][j]->flag == false) {
                                this->isWin = false;
                                break;
                            }
                        }
                        if (this->isWin == false) {
                            break;
                        }
                    }
                    if (this->isWin == true) {
                        // 胜利了
                        winSound->setLoops(1);
                        winSound->play();
                        qDebug() << "胜利了";
                        // 将所有按钮的胜利标志改为 true
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                        // 将胜利的图片移动下来
                        QPropertyAnimation* animation = new QPropertyAnimation(winLabel, "geometry");
                        // 设置事件间隔
                        animation->setDuration(1000);
                        // 设置开始位置
                        animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        // 设置结束位置
                        animation->setEndValue(QRect(winLabel->x(), winLabel->y()+124, winLabel->width(), winLabel->height()));
                        // 设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent* ) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    // 加载标题
    pix.load(":/Title.png");
    pix = pix.scaled(int(pix.width() * 0.5), int(pix.height() * 0.5));
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}
