#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "mycoin.h"
#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(int levelNum);
    // 重写 paintEvent 事件
    void paintEvent(QPaintEvent*);

private:
    int levelIndex; // 内部成员属性 记录所选关卡
    int gameArray[4][4]; // 二维数组 维护每个关卡的具体数据
    MyCoin* coinBtn[4][4];
    // 是否胜利的标志
    bool isWin;

signals:
    void chooseSceneBack();

public slots:
};

#endif // PLAYSCENE_H
