#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
//#include<map>
#include <QApplication>

using namespace std;

bool lift = true;
QPushButton* moveFromButtonPtr= nullptr;
QLabel* moveFromLabelPtr= nullptr;
QLabel* targetLabelPtr = nullptr;
QPushButton* moveToButtonPtr = nullptr;
QPushButton* moveToLabelPtr= nullptr;

QList<QLabel*> hitPiecePtrList_b;
map<string, QLabel*> m_b;

QList<QLabel*> hitPiecePtrList_y;
map<string, QLabel*> m_y;
bool endGameNow = false;
bool isBlueTurn = true; // blue부터 시작



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
