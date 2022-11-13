#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H

#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <stdexcept>

namespace Ui { class MainWindow; }
using namespace std;

extern bool isLiftTurn;
extern bool isBlueTurn;
extern bool endGameNow;
extern int hitPieceCount_b;
extern int hitPieceCount_y;

extern string moveFromButtonName;
extern QLabel* movingLabelPtr;

extern map<string, QLabel*> map_s_Q;

void Pick(string pickedButtonName, QLabel*& pickedLabelPtr) {
    if (pickedLabelPtr != nullptr) { // When the label exists,
        string pickedLabelcolor = pickedLabelPtr->objectName().toStdString().substr(0,1);
        if (isBlueTurn && pickedLabelcolor== "y") {
            throw invalid_argument("THIS_IS_BLUE'S_TURN");
        } else if (!isBlueTurn && pickedLabelcolor== "b") {
            throw invalid_argument("THIS_IS_YELLOW'S_TURN");
        } else {
            moveFromButtonName = pickedButtonName; // store the position.
            movingLabelPtr = pickedLabelPtr;
        }
    } else { // when the label donesn't exist
        throw logic_error("USER_CLICKED_EMPTY_PLACE");
    }
}


void Move(bool isBlueTurn, QLabel* movingLabelPtr, string moveFromButtonName, string moveToButtonName){
    int fromX = stoi(moveFromButtonName.substr(2,1));
    int fromY = stoi(moveFromButtonName.substr(4,1));

    int toX = stoi(moveToButtonName.substr(2,1));
    int toY = stoi(moveToButtonName.substr(4,1));

    if (abs(toX-fromX) ==1 && abs(toY-fromY)==1) {
        movingLabelPtr->move(35+(toX-1)*64, 30+(toY-1)*64);
        QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
        map_s_Q[moveFromButtonName] = nullptr;
        map_s_Q[moveToButtonName] = tempLabelPtr;
    } else if (abs(toX-fromX) ==2 && abs(toY-fromY)==2){
        string midX = to_string(fromX+(int)(toX-fromX)/2);
        string midY = to_string(fromY+(int)(toY-fromY)/2);
        string midButtonName = "B_";
        midButtonName.append(midX);
        midButtonName.append("_");
        midButtonName.append(midY);
        QLabel* midLabelPtr = map_s_Q.at(midButtonName);
        if (isBlueTurn){
            string color = midLabelPtr->objectName().toStdString().substr(0,1);
            if (color=="y"){
                movingLabelPtr->move(35+(toX-1)*64, 30+(toY-1)*64);
                QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
                map_s_Q[moveFromButtonName] = nullptr;
                map_s_Q[moveToButtonName] = tempLabelPtr;
                hitPieceCount_b++;
                map_s_Q.at(midButtonName)->setVisible(false);
                map_s_Q[midButtonName] = nullptr;
            }else{
                 throw invalid_argument("INVALID_PIECE_COLOR_IN_MIDDLE");
            }
        } else {
            string color = midLabelPtr->objectName().toStdString().substr(0,1);
            if (color=="b"){
                movingLabelPtr->move(35+(toX-1)*64, 30+(toY-1)*64);
                QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
                map_s_Q[moveFromButtonName] = nullptr;
                map_s_Q[moveToButtonName] = tempLabelPtr;
                hitPieceCount_y++;
                map_s_Q.at(midButtonName)->setVisible(false);
                map_s_Q[midButtonName] = nullptr;
            } else{
                throw invalid_argument("INVALID_PIECE_COLOR_IN_MIDDLE");
            }
        }

    } else{
        throw range_error("INVALID_MOVEMENT");
    }
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

void CheckAndHandleWinCase(Ui::MainWindow* ui) {
    if (!isWinnerDecided()){return;}
    ui->stackedWidget->setCurrentWidget(ui->page_4);
    if (getWinner() == "blue"){
        ui->comment_4->setFont(QFont("Cooper Black",20));
        ui->comment_4->setText("Blue had won the game!");

    } else if (getWinner()=="yellow"){
        ui->comment_4->setFont(QFont("Cooper Black",20));
        ui->comment_4->setText("Yellow had won the game!");
    } else{ //tie
        ui->comment_4->setFont(QFont("Cooper Black",20));
        ui->comment_4->setText("Tie!");
    }
}
