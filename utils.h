#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H

#include <string>
#include <QLabel>
using namespace std;

int getIndexFromPieceButtonName(string pieceButtonName){
    if (pieceButtonName.length() == 8) { // When the index of pieceButton is one digit (e.g. b9Button)
        return (int)pieceButtonName[1];
    } else { // When the index of pieceButton is two digits (e.g. b10Button)
        return (int)stoi(pieceButtonName.substr(1,2)); // two digit from the second char(index -> 1)
    }
}

bool isButtonBlue(string pieceButtonName){
    if (pieceButtonName[0] == 'b'){
        return true;
    } else {
        return false;
    }
}

bool isMoveAllowed(QLabel* startLabel, QLabel* endLabel){
    //Todo moveFromLabel에서 moveFromLabel까지 움직일 수 있는 지 확인하기
    return true; // Todo
}

QLabel* GetRemoveableTarget(QLabel* startLabel, QLabel* endLabel){
    //Todo
    return startLabel;
}
