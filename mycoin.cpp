#include "mycoin.h"
#include <QPixmap>
#include <QDebug>

MyCoin::MyCoin(QString btnImage) {
    QPixmap pix;
    bool res = pix.load(btnImage);
    if (!res) {
        QString str = QString("图片 %1 加载失败").arg(btnImage);
        qDebug() << str;
        return;
    }
    pix = pix.scaled(int(pix.width()*1.5), int(pix.height()*1.5));
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    // 初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    // 监听正面翻反面的信号，并且翻转金币
    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str = QString(":/Coin000%1.png").arg(this->min++);
        pix.load(str);
        pix = pix.scaled(int(pix.width()*1.5), int(pix.height()*1.5));
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        // 如果翻完了，将 min 重置为 1
        if (this->min > this->max) {
            this->min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });

    connect(timer2, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/Coin000%1.png").arg(this->max--);
        pix.load(str);
        pix = pix.scaled(int(pix.width()*1.5), int(pix.height()*1.5));
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        // 如果翻完了，将 max 重置为 8
        if (this->min > this->max) {
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });
}

void MyCoin::changeFlag() {
    // 如果是正面，则翻成反面
    if (this->flag) {
        // 开始正面翻反面的定时器
        timer1->start(30);
        isAnimation = true; // 开始做动画
        this->flag = false;

    } else {
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent* e) {
    if (this->isAnimation || this->isWin) {
        return;
    } else {
        QPushButton::mousePressEvent(e);
    }
}
