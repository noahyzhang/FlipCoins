#ifndef MYPUSHBUTOON_H
#define MYPUSHBUTOON_H

#include <QPushButton>

class MyPushButoon : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButoon(QString normalImg, QString pressImg = "");
    void zoom(bool flag); // 弹跳
    // 重写按钮 按下和释放 事件
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
private:
    QString normalImagePath;
    QString pressImagePath;

signals:

public slots:
};

#endif // MYPUSHBUTOON_H
