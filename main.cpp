#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int currentExitCode = 0;

    do {
     QApplication a(argc, argv);
     Enemy::add_score = 10;
     MainWindow w;
     w.show();
     currentExitCode = a.exec();
    } while( currentExitCode == MainWindow::EXIT_CODE_REBOOT );

    return currentExitCode;


}
