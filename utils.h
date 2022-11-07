#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H

#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLabel>


namespace Ui { class MainWindow; }

using namespace std;
extern map<string, QLabel*> map_s_Q;
extern QList<QLabel*> hitPiecePtrList_b;
extern QList<QLabel*> hitPiecePtrList_y;
extern int hitPieceCount_b;
extern int hitPieceCount_y;

bool isMoveAllowed(bool isBlueTurn, string moveFromButtonName, string moveToButtonName){
    int fromX = stoi(moveFromButtonName.substr(2,1));
    int fromY = stoi(moveFromButtonName.substr(4,1));

    int toX = stoi(moveToButtonName.substr(2,1));
    int toY = stoi(moveToButtonName.substr(4,1));
    if (abs(toX-fromX) ==1 && abs(toY-fromY)==1) {
        return true;
    } else if (abs(toX-fromX) ==2 && abs(toY-fromY)==2){
        string midX = to_string(fromX+(int)(toX-fromX)/2);
        string midY = to_string(fromY+(int)(toY-fromY)/2);
        string midButtonName = "B_";
        midButtonName.append(midX);
//        string underscore = ("_");
        midButtonName.append("_");
        midButtonName.append(midY);
        QLabel* midLabelPtr = map_s_Q.at(midButtonName);
        if (isBlueTurn){
//            if (midLabelPtr->property("color").value<string>()=="y"){
            string color = midLabelPtr->objectName().toStdString().substr(0,1);
            if (color=="y"){
                return true;
            }else{
                return false;
            }
        } else {
//            if (midLabelPtr->property("color").value<string>()=="b"){
            string color = midLabelPtr->objectName().toStdString().substr(0,1);
            if (color=="b"){
                return true;
            } else{
                return false;
            }
        }

    } else{return false;}
}

int MoveAndGetMoveType(QLabel* &moveFromLabelPtr, string moveFromButtonName, string moveToButtonName){
    int fromX = stoi(moveFromButtonName.substr(2,1));
    int toX = stoi(moveToButtonName.substr(2,1));
    int toY  = stoi(moveToButtonName.substr(4,1));
    moveFromLabelPtr->move(35+(toX-1)*64, 30+(toY-1)*64);
    QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
    map_s_Q[moveFromButtonName] = nullptr;
    map_s_Q[moveToButtonName] = tempLabelPtr;
    if (abs(toX-fromX)==2){
        return 2; //다른 팀 말을 건너뛰어서 움직이는 형태
    } else{
        return 1; // 그냥 이동만 하는 형태
    }
}

void RemoveLabelInBetween(bool isBlueTurn, string moveFromButtonName, string moveToButtonName){
//    //Todo
////    QLabel* targetPiecePtr; // 가운데 있는 상대 말은 삼키기
////    targetPiecePtr = GetRemoveableTarget(moveFromButtonPtr, moveToButtonPtr);
////    if (targetPiecePtr != NULL){ /* 기억하고 있는 말과 클릭한 곳 사이에 말을 딸 수 있다면*/
////        hitPiecePtrList.push_back(targetPiecePtr);
////    } else {
////        //pass
    int fromX = stoi(moveFromButtonName.substr(2,1));
    int fromY = stoi(moveFromButtonName.substr(4,1));

    int toX = stoi(moveToButtonName.substr(2,1));
    int toY = stoi(moveToButtonName.substr(4,1));

    string midX = to_string(fromX+(int)(toX-fromX)/2);
    string midY = to_string(fromY+(int)(toY-fromY)/2);
    string midButtonName = "B_";
    midButtonName.append(midX);
    midButtonName.append("_");
    midButtonName.append(midY);
    if (isBlueTurn){
        hitPiecePtrList_b.push_back(map_s_Q.at(midButtonName));
        hitPieceCount_b++;
    }else{
        hitPiecePtrList_y.push_back(map_s_Q.at(midButtonName));
        hitPieceCount_y++;
    }
    map_s_Q.at(midButtonName)->setVisible(false);
    map_s_Q[midButtonName] = nullptr;
}

bool isWinnerDecided(){
    if (hitPieceCount_b==12 || hitPieceCount_y==12){
        return true;
    }
    return false;
}

string getWinner(){
    if (hitPieceCount_b==12){
        if (hitPieceCount_y==12){
            return "tie";
        }
        return "blue";
    }
    return "yellow";
}
