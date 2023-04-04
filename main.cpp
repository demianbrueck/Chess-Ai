#include "mainwindow.h"
#include <chessai.h>
#include <figures.h>
#include <QObject>

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Chess");
    ChessAi chessAi(&mainWindow);
    QObject::connect(&mainWindow,SIGNAL(sigGetAiMove(QVector<Figures *>, int)),&chessAi,SLOT(slotGetAiMove(QVector<Figures *>, int)));
    QObject::connect(&chessAi,SIGNAL(sigAiMoveReady()),&mainWindow,SLOT(slotAiMoveReady()));

    mainWindow.setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    mainWindow.show();

    return a.exec();
}
