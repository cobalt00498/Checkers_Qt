#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QApplication>

using namespace std;

bool isLiftTurn = true;
string moveFromButtonName;
QLabel* movingLabelPtr= nullptr;
QLabel* targetLabelPtr = nullptr;
string moveToButtonName;

QList<QLabel*> hitPiecePtrList_b;
int hitPieceCount_b = 0;
QList<QLabel*> hitPiecePtrList_y;
int hitPieceCount_y = 0;
bool endGameNow = false;
bool isBlueTurn = true;

map<string, QLabel*> map_s_Q;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
