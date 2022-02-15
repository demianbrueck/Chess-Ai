#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <vector>
#include <string.h>
#include <QDebug>
#include <QWheelEvent>
#include <QThread>
#include <fstream>
#include <cstring>
#include "figures.h"
#include <QMediaPlayer>
#include <QSound>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define BLOCK_WIDTH 125
#define BLOCK_HEIGHT 125
#define BLACK true
#define WHITE false

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void sysTickTimer();
private:
    Ui::MainWindow *ui;
    QTimer * m_pSysTickTimer;
    float chessFieldWidth;
    float chessFieldHeight;
    bool blackFieldColor;
    Figures * m_pFigures[32];
    Figures * m_pFiguresCopy[32];
    int m_amountFigures;
    QPoint getField(float,float);
    int getFigureOnPos(float,float);
    int activeFigure;
    QMediaPlayer * musicPlayer;
    bool captured;
    void refreshCurrentlyPossibleMoves();
    bool colorTurn;
    void getAiMove();
    int depth;
    int highestAiValue;
    int bestAiMoveFigure;
    QPoint bestAiMove;


};
#endif // MAINWINDOW_H
