#include "mainwindow.h"
#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(time(0));

    MainWindow w;
    w.show();

    return a.exec();
}
