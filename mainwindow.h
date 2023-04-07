#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QVector>
#include <string.h>
#include <QDebug>
#include <QWheelEvent>
#include <QThread>
#include <fstream>
#include <cstring>
#include "figures.h"
#include <QMediaPlayer>
#include <QSound>
#include <QObject>

#define AMOUNT_FIGURES 32
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define BLOCK_WIDTH 125
#define BLOCK_HEIGHT 125
#define BLACK true
#define WHITE false
#define NONE 999
#define AI_DEPTH 8
#define DEBUG_MODE false

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refreshCurrentlyPossibleMoves(bool color);
    int bestAiMoveFigure;
    QPoint bestAiMove;


signals:
    void sigGetAiMove(QVector<Figures*> pFigures,int depth);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void sysTickTimer();
    void slotAiMoveReady();
private:
    Ui::MainWindow *ui;
    QTimer * m_pSysTickTimer;
    float chessFieldWidth;
    float chessFieldHeight;
    bool blackFieldColor;
    QVector<Figures*> m_pFigures;
    QVector<Figures*> m_pFiguresCopy;
    int m_amountFigures;
    QPoint getField(float,float);
    int getFigureOnPos(float,float);
    int activeFigure;
    QMediaPlayer * musicPlayer;
    bool captured;
    bool colorTurn;
    void getAiMove();
    int lowestAiMoves;
    bool generatingAiMove;

};
#endif // MAINWINDOW_H
