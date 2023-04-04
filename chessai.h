#ifndef CHESSAI_H
#define CHESSAI_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <figures.h>
#include <mainwindow.h>

#define AMOUNT_FIGURES 32

class ChessAi : public QThread
{
    Q_OBJECT
public:
    ChessAi(MainWindow *pMainWindow);
    void run() override;
signals:
    void sigAiMoveReady();

public slots:
    void slotGetAiMove(QVector<Figures*> pFigures,int depth);
private:
    QVector<Figures*> m_pFigures;
    QVector<Figures> m_figuresCopy;
    int m_aiDepth;
    MainWindow * m_pMainWindow;
    int aiValue;
    int aiMoves;
    int highestAiValue;
    int capturedAtWhichAiMove;
    QVector<MainWindow::Move> initalPossibleAiMoves;
    MainWindow::Move move;
};

#endif // CHESSAI_H
