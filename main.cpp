#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

#include <QApplication>

using namespace std;

bool lift = true;
QLabel* moveFromLabel = nullptr;
QLabel* targetLabel = nullptr;
QLabel* moveToLabel = nullptr;
QList<QLabel*> hitPieces;
bool endGameNow = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
