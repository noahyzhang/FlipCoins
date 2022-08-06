#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QWidget>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    // 重写绘图事件
    void paintEvent(QPaintEvent*);

private:
    PlayScene* play = nullptr;

signals:
    // 写一个自定义的信号，告诉主场景 点击了返回
    void chooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
