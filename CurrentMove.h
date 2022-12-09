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

    // Faicilitators
    // Set the button name that the move starts from.
    void setMoveFromButtonName(string buttonName){
        moveFromButtonName = buttonName;
    };
    // Set the button name that the label move to.
    void setMoveToButtonName(string buttonName){
        moveToButtonName = buttonName;
    };
    // Set the pointer of the moving label.
    void setMovingLabelPtr(QLabel* labelPtr){
        movingLabelPtr = labelPtr;
    };
    // Get the button name that the move starts from.
    string getMoveFromButtonName(){
        return moveFromButtonName;
    };

    // Get the button name that the label move to.
    string getMoveToButtonName(){
        return moveToButtonName;
    };
    // Get the pointer of the moving label.
    QLabel* getMovingLabelPtr(){
        return movingLabelPtr;
    };
    // Pick the piece.
    void pickPiece(string, QLabel*&);
    // Move the piece.(Same as 'Dropping the piece')
    void movePiece(string);
private:
    string moveFromButtonName; // This variable stores the button name where the piece move from.
    string moveToButtonName; // This variable stores the button name where the piece move to.
    QLabel* movingLabelPtr; // This variable stores the pointer to the label(piece).
};
