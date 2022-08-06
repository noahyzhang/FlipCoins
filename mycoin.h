#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QString btnImage);
    // 改变标志的方法
    void changeFlag();
    // 重写 按下
    void mousePressEvent(QMouseEvent*);

public:
    int posX;  // x 坐标位置
    int poxY;  // y 坐标位置
    bool flag; // 正反面
    QTimer* timer1;  // 正面翻反面的定时器
    QTimer* timer2;  // 反面翻正面的定时器
    int min = 1;
    int max = 8;
    // 执行动画标志
    bool isAnimation = false;
    bool isWin = false;


signals:

public slots:
};

#endif // MYCOIN_H
