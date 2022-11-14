#ifndef MOVE_H
#define MOVE_H

#endif // MOVE_H
#include <QtWidgets/QLabel>
#include <iostream>
using namespace std;

// Move class contains two major movement, pick and move(drop).
class Move
{
    public:
        static void pickPiece(string, QLabel*&);
        static void movePiece(QLabel*, string, string);
};
