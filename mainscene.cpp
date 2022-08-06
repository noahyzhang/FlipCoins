#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutoon.h"
#include <QPainter>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    ui->menubar->setNativeMenuBar(false);

    // 配置主场景
    // 设置固定大小
    setFixedSize(420, 588);
    // 设置图标
    setWindowIcon(QIcon(":/Coin0001.png"));
    // 设置标题
    setWindowTitle("翻金币");
    // 退出按钮
    connect(ui->actionquit, &QAction::triggered, [=]() {
        this->close();
    });
    // 准备开始按钮的音效
    QSound* startSound = new QSound(":/TapButtonSound.wav", this);

    // 开始按钮
    MyPushButoon* startBtn = new MyPushButoon(":/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(int(this->width()*0.5) - int(startBtn->width()*0.5), int(this->height()*0.7));
    // 实例化选择关卡场景
    chooseScene = new ChooseLevelScene();

    // 监听选择关卡的返回按钮的信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [=]() {
        QTimer::singleShot(300, this, [=]() {
            this->setGeometry(chooseScene->geometry());
            chooseScene->hide();
            this->show();
        });
    });

    connect(startBtn, &MyPushButoon::clicked, [=](){
        // 弹起特效
        startSound->play();
        startBtn->zoom(true);
        startBtn->zoom(false);
        // 进入选择关卡场景
        // 自身隐藏，显示关卡场景
        // 加入延时
        QTimer::singleShot(300, this, [=](){
            // 设置 chooseScene 场景的位置
            chooseScene->setGeometry(this->geometry());
            this->hide();
            chooseScene->show();

        });
    });

}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    // 画背景图标
    pix.load(":/Title.png");
    pix = pix.scaled(int(pix.width() * 0.5), int(pix.height() * 0.5));
    painter.drawPixmap(10, 30, pix);
}

