# pragma once
#ifndef CURRENTMOVE_H
#define CURRENTMOVE_H

#endif // CURRENTMOVE_H
#include <QtWidgets/QLabel>
#include <iostream>
using namespace std;

// CurrentMove class contains two major movement, pick and move(drop).
class CurrentMove
{
public:
    static CurrentMove createCurrentMove(){
        return CurrentMove();
    };
    CurrentMove(); // Constructor
    void setMoveFromButtonName(string buttonName){
        moveFromButtonName = buttonName;
    };

    void setMoveToButtonName(string buttonName){
        moveToButtonName = buttonName;
    };

    void setMovingLabelPtr(QLabel* labelPtr){
        movingLabelPtr = labelPtr;
    };

    string getMoveFromButtonName(){
        return moveFromButtonName;
    };
    string getMoveToButtonName(){
        return moveToButtonName;
    };
    QLabel* getMovingLabelPtr(){
        return movingLabelPtr;
    };

    void pickPiece(string, QLabel*&);
    void movePiece(string);
private:
    string moveFromButtonName; // This variable stores the button name where the piece move from.
    string moveToButtonName; // This variable stores the button name where the piece move to.
    QLabel* movingLabelPtr; // This variable stores the pointer to the label(piece).
};
