#include "mypushbutoon.h"
#include <QDebug>
#include <QPropertyAnimation>

MyPushButoon::MyPushButoon(QString normalImg, QString pressImg) {
    this->normalImagePath = normalImg;
    this->pressImagePath = pressImg;

    QPixmap pix;
    bool res = pix.load(normalImg);
    if (!res) {
        qDebug() << "图片加载失败";
        return;
    }
    // 设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());
    // 设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    // 设置图标
    this->setIcon(pix);
    // 设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));
}

void MyPushButoon::zoom(bool flag) {
    // 创建动态对象
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    // 设置动画时间间隔
    animation->setDuration(200);
    if (flag) {
        // 起始位置
        animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
        // 结束位置
        animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    } else {
        // 起始位置
        animation->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
        // 结束位置
        animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    }
    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    // 执行动画
    animation->start();
}

void MyPushButoon::mousePressEvent(QMouseEvent* e) {
    // 传入的按下图片不为空 说明需要有按下状态 切换图片
    if (this->pressImagePath != "") {
        QPixmap pix;
        bool res = pix.load(this->pressImagePath);
        if (!res) {
            qDebug() << "图片加载失败";
            return;
        }
        // 设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        // 设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        // 设置图标
        this->setIcon(pix);
        // 设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    // 让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButoon::mouseReleaseEvent(QMouseEvent* e) {
    if (this->pressImagePath != "") {
        QPixmap pix;
        bool res = pix.load(this->normalImagePath);
        if (!res) {
            qDebug() << "图片加载失败";
            return;
        }
        // 设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        // 设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        // 设置图标
        this->setIcon(pix);
        // 设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    // 让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}


