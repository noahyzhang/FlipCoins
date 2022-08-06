#include "chooselevelscene.h"
#include "mypushbutoon.h"
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <QDebug>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent) {
    // 配置选择关卡场景
    this->setFixedSize(420, 588);
    // 设置图标
    this->setWindowIcon(QPixmap(":/Coin0001.png"));
    // 设置标题
    this->setWindowTitle("选择关卡场景");
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
        // 告诉主场景，我返回了。主场景监听 chooseLevelScene 的返回按钮
        emit this->chooseSceneBack();
    });
    // 创建选择关卡的按钮
    for (int i = 0; i < 20; i++) {
        MyPushButoon* menubtn = new MyPushButoon(":/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(70 + i % 4 * 70, 150 + i / 4 * 70);

        // 监听每个按钮的点击事件
        connect(menubtn, &MyPushButoon::clicked, [=](){
            QString str = QString("您选择的是第 %1 关").arg(i+1);
            qDebug() << str;
            // 进入游戏场景
            this->hide();
            play = new PlayScene(i+1);
            // 设置游戏场景的初始化位置
            play->setGeometry(this->geometry());
            play->show();

            connect(play, &PlayScene::chooseSceneBack, [=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = nullptr;
            });
        });

        QLabel* label = new QLabel();
        label->setParent(this);
        label->setFixedSize(menubtn->width(), menubtn->height());
        label->setText(QString::number(i+1));
        label->move(70 + i % 4 * 70, 150 + i / 4 * 70);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        // 设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/Title.png");
    painter.drawPixmap(int((this->width() - pix.width())*0.5), 30, pix.width(), pix.height(), pix);
}
