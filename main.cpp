#include "mainwindow.h"
#include "figures.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Chess");
    mainWindow.setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    mainWindow.show();

    return a.exec();
}
