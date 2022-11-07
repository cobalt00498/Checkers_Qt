#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
//#include<map>
#include <QApplication>

using namespace std;

bool lift = true;
string moveFromButtonName;
QLabel* movingLabelPtr= nullptr;
QLabel* targetLabelPtr = nullptr;
string moveToButtonName;
//QPushButton* moveToLabelPtr= nullptr;

QList<QLabel*> hitPiecePtrList_b;
int hitPieceCount_b = 0;
QList<QLabel*> hitPiecePtrList_y;
int hitPieceCount_y = 0;
bool endGameNow = false;
bool isBlueTurn = true; // blue부터 시작
bool moveDone = false;
map<string, QLabel*> map_s_Q;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
